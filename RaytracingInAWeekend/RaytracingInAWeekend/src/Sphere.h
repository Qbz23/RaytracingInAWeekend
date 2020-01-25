#pragma once
#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:
    Sphere() { m_pMaterial = nullptr; };
    Sphere(Vec3 center, float r, Material* pMat) : 
        m_Center(center), m_Radius(r), m_pMaterial(pMat) {}

    ~Sphere()
    {
        if (m_pMaterial)
        {
            delete m_pMaterial;
        }
    }

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override;

private:
    Vec3 m_Center;
    float m_Radius;
    Material* m_pMaterial;
};
