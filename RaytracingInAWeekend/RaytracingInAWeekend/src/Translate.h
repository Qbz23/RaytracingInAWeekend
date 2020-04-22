#pragma once

#include "Hittable.h"

class Translate : public Hittable
{
public:
    Translate(Hittable* pHittable, const Vec3& offset) : 
        m_pHittable(pHittable), m_Offset(offset) {}

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override
    {
        Ray movedRay(r.Origin() - m_Offset, r.Direction(), r.Time());
        if (!m_pHittable->Hit(movedRay, tMin, tMax, hr))
        {
            return false;
        }

        hr.point += m_Offset;
        hr.SetFaceNormal(movedRay, hr.normal);

        return true;
    }

    virtual bool BoundingBox(float t0, float t1, AABB& outBox) const override
    {
        if (!m_pHittable->BoundingBox(t0, t1, outBox))
        {
            return false;
        }

        outBox = AABB(
            outBox.Min() + m_Offset,
            outBox.Max() + m_Offset);

        return true;
    }

private:
    Hittable* m_pHittable;
    const Vec3 m_Offset;
};
