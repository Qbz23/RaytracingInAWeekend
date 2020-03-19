#pragma once

#include "Hittable.h"

class YZRect : public Hittable
{
public:
    YZRect() {}
    ~YZRect() { if (m_pMat != nullptr) delete m_pMat; }
    YZRect(float y0, float y1, float z0, float z1, float k, Material* pMat) :
        m_Y0(y0), m_Y1(y1), m_Z0(z0), m_Z1(z1), m_K(k), m_pMat(pMat) {}

    virtual bool Hit(const Ray& r, float t0, float t1, HitRecord& hr) const override
    {
        float t = (m_K - r.Origin().X()) / r.Direction().X();
        if (t < t0 || t > t1)
        {
            return false;
        }

        float y = r.Origin().Y() + t * r.Direction().Y();
        float z = r.Origin().Z() + t * r.Direction().Z();
        if (y < m_Y0 || y > m_Y1 || z < m_Z0 || z > m_Z1)
        {
            return false;
        }

        hr.u = (y - m_Y0) / (m_Y1 - m_Y0);
        hr.v = (z - m_Z0) / (m_Z1 - m_Z0);
        hr.pMaterial = m_pMat;
        hr.point = r.Point(t);
        hr.normal = Vec3(1, 0, 0);
        return true;
    }

    virtual bool BoundingBox(float t0, float t1, AABB& box) const
    {
        box = AABB(
            Vec3(m_K - 0.001f, m_Y0, m_Z0),
            Vec3(m_K + 0.001f, m_Y1, m_Z1));
        return true;
    }

private:
    float m_Y0;
    float m_Y1;
    float m_Z0;
    float m_Z1;
    float m_K;
    Material* m_pMat = nullptr;
};