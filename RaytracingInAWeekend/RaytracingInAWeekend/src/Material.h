#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "Helpers.h"
#include "Texture.h"

class Material
{
public:
    virtual ~Material() { }
    virtual bool Scatter(
        const Ray& rIn, 
        const HitRecord& hr,
        Vec3& attenuation,
        Ray& scattered
    ) const = 0;

    virtual Vec3 Emitted(float u, float v, const Vec3& p)
    {
        return Vec3(0.f, 0.f, 0.f);
    }
};

class Lambertian : public Material
{
public:
    Lambertian() : m_pAlbedo(nullptr) {}
    Lambertian(Texture* pA) : m_pAlbedo(pA) {}
    ~Lambertian()
    { 
        if (m_pAlbedo) 
        { 
            delete m_pAlbedo; 
        } 
    }

    virtual bool Scatter(const Ray& rIn, const HitRecord& hr,
        Vec3& attenuation, Ray& scattered) const override
    {
        Vec3 target = hr.point + hr.normal + Helpers::RandomPointInUnitSphere();
        scattered = Ray(hr.point, target - hr.point, rIn.Time());
        attenuation = m_pAlbedo->Value(hr.u, hr.v, hr.point);
        return true;
    }

private:
    Texture* m_pAlbedo;
};

class Metal : public Material
{
public:
    Metal(const Vec3& a, float f) : m_Albedo(a) 
    {
        m_Fuzz = f < 1 ? f : 1;
    }

    virtual bool Scatter(const Ray& rIn, const HitRecord& hr,
        Vec3& attenuation, Ray& scattered) const override
    {
        Vec3 unitDir = rIn.Direction().GetNormalized();
        Vec3 reflected = unitDir.Reflect(hr.normal);
        scattered = Ray(
            hr.point,
            reflected + m_Fuzz * Helpers::RandomPointInUnitSphere(),
            rIn.Time()
        );
        attenuation = m_Albedo;
        return ((scattered.Direction().Dot(hr.normal)) > 0);
    }

private:
    Vec3 m_Albedo;
    float m_Fuzz;
};

class Dielectric : public Material
{
public:
    Dielectric(float ri) : m_RefractionIndex(ri) {}

    virtual bool Scatter(const Ray& rIn, const HitRecord& hr,
        Vec3& attenuation, Ray& scattered) const override
    {
        Vec3 normal;
        Vec3 reflected = rIn.Direction().Reflect(hr.normal);
        float niOverNt;
        attenuation = Vec3(1.0f, 1.0f, 1.0f);
        Vec3 refracted;

        float reflectProb;
        float cosine;

        if (rIn.Direction().Dot(hr.normal) > 0.0f)
        {
            normal = -hr.normal;
            niOverNt = m_RefractionIndex;
            cosine = m_RefractionIndex * rIn.Direction().Dot(hr.normal) / rIn.Direction().Length();
        }
        else
        {
            normal = hr.normal;
            niOverNt = 1.0f / m_RefractionIndex;
            cosine = -rIn.Direction().Dot(hr.normal) / rIn.Direction().Length();
        }

        if (rIn.Direction().Refract(normal, niOverNt, refracted))
        {
            reflectProb = Helpers::Schlick(cosine, m_RefractionIndex);
        }
        else
        {
            reflectProb = 1.0f;
        }

        if (Helpers::RandomFloat() < reflectProb)
        {
            scattered = Ray(hr.point, reflected, rIn.Time());
        }
        else 
        {
            scattered = Ray(hr.point, refracted, rIn.Time());
        }

        return true;
    }

private:
    float m_RefractionIndex;
};
