#pragma once
#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:
    Sphere() { m_pMaterial = nullptr; };
    Sphere(Vec3 center0, Vec3 center1, float r, Material* pMat) : 
        m_Center0(center0), m_Center1(center1), m_Radius(r), m_pMaterial(pMat) {}

    ~Sphere()
    {
        if (m_pMaterial)
        {
            delete m_pMaterial;
        }
    }

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override;
    Vec3 Center(float time) const
    {
        // assume t0 == 0 && t1 == 1, param = [0, 1]
        return time * m_Center0 + (1.0f - time) * m_Center1;
    }

private:
    Vec3 m_Center0;
    Vec3 m_Center1;
    float m_Radius;
    Material* m_pMaterial;
};
