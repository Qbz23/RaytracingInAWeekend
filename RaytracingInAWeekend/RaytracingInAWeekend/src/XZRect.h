#pragma once

#include "Hittable.h"

class XZRect : public Hittable
{
public:
    XZRect() {}
    ~XZRect() { /*if (m_pMat != nullptr) delete m_pMat;*/ }
    XZRect(float x0, float x1, float z0, float z1, float k, Material* pMat) :
        m_X0(x0), m_X1(x1), m_Z0(z0), m_Z1(z1), m_K(k), m_pMat(pMat) {}

    virtual bool Hit(const Ray& r, float t0, float t1, HitRecord& hr) const override
    {
        float t = (m_K - r.Origin().Y()) / r.Direction().Y();
        if (t < t0 || t > t1)
        {
            return false;
        }

        float x = r.Origin().X() + t * r.Direction().X();
        float z = r.Origin().Z() + t * r.Direction().Z();
        if (x < m_X0 || x > m_X1 || z < m_Z0 || z > m_Z1)
        {
            return false;
        }

        hr.t = t;
        hr.u = (x - m_X0) / (m_X1 - m_X0);
        hr.v = (z - m_Z0) / (m_Z1 - m_Z0);
        hr.pMaterial = m_pMat;
        hr.point = r.Point(t);
        hr.normal = Vec3(0, 1, 0);
        return true;
    }

    virtual bool BoundingBox(float t0, float t1, AABB& box) const
    {
        box = AABB(
            Vec3(m_X0, m_K - 0.001f, m_Z0),
            Vec3(m_X1, m_K + 0.001f, m_Z1));
        return true;
    }

private:
    float m_X0;
    float m_X1;
    float m_Z0;
    float m_Z1;
    float m_K;
    Material* m_pMat = nullptr;
};