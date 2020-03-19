#pragma once

#include "Hittable.h"

class XYRect : public Hittable
{
public:
    XYRect() {}
    ~XYRect() { if (m_pMat != nullptr) delete m_pMat; }
    XYRect(float x0, float x1, float y0, float y1, float k, Material* pMat) :
        m_X0(x0), m_X1(x1), m_Y0(y0), m_Y1(y1), m_K(k), m_pMat(pMat) {}

    virtual bool Hit(const Ray& r, float t0, float t1, HitRecord& hr) const override
    {
        float t = (m_K - r.Origin().Z()) / r.Direction().Z();
        if (t < t0 || t > t1)
        {
            return false;
        }

        float x = r.Origin().X() + t * r.Direction().X();
        float y = r.Origin().Y() + t * r.Direction().Y();
        if (x < m_X0 || x > m_X1 || y < m_Y0 || y > m_Y1)
        {
            return false;
        }

        hr.u = (x - m_X0) / (m_X1 - m_X0);
        hr.v = (y - m_Y0) / (m_Y1 - m_Y0);
        hr.pMaterial = m_pMat;
        hr.point = r.Point(t);
        hr.normal = Vec3(0, 0, 1);
        return true;
    }

    virtual bool BoundingBox(float t0, float t1, AABB& box) const
    {
        box = AABB(
            Vec3(m_X0, m_Y0, m_K - 0.001f),
            Vec3(m_X1, m_Y1, m_K + 0.001f));
        return true;
    }

private:
    float m_X0;
    float m_X1;
    float m_Y0;
    float m_Y1;
    float m_K;
    Material* m_pMat = nullptr;
};