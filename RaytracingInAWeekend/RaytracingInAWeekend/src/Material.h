#pragma once
#include "Ray.h"
#include "Hittable.h"
#include "Helpers.h"

class Material
{
public:
    virtual bool Scatter(
        const Ray& rIn, 
        const HitRecord& hr,
        Vec3& attenuation,
        Ray& scattered
    ) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vec3& a) : m_Albedo(a) {}

    virtual bool Scatter(const Ray& rIn, const HitRecord& hr,
        Vec3& attenuation, Ray& scattered) const override
    {
        Vec3 target = hr.point + hr.normal + Helpers::RandomPointInUnitSphere();
        scattered = Ray(hr.point, target - hr.point);
        attenuation = m_Albedo;
        return true;
    }

private:
    Vec3 m_Albedo;
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
        scattered = Ray(hr.point, reflected + m_Fuzz * Helpers::RandomPointInUnitSphere());
        attenuation = m_Albedo;
        return ((scattered.Direction().Dot(hr.normal)) > 0);
    }


private:
    Vec3 m_Albedo;
    float m_Fuzz;
};
