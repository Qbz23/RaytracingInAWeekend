#pragma once

#include "Hittable.h"
#include "Material.h"

class ConstantMedium : public Hittable
{
public:
    ConstantMedium(Hittable* pBoundary, float density, Texture* pTex) : m_pBoundary(pBoundary),
        m_pPhaseFunction(new Isotropic(pTex)), negInverseDensity(-1.0f/density) {}

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override
    {
        HitRecord hr1, hr2;
        if (!m_pBoundary->Hit(r, -INFINITY, INFINITY, hr1))
        {
            return false;
        }

        if (!m_pBoundary->Hit(r, hr1.t+0.001f, INFINITY, hr2))
        {
            return false;
        }

        if (hr1.t < tMin) hr1.t = tMin;
        if (hr2.t > tMax) hr2.t = tMax;

        if (hr1.t >= hr2.t)
        {
            return false;
        }

        if (hr1.t < 0)
        {
            hr1.t = 0.0f;
        }
        
        float rayLength = r.Direction().Length();
        float distanceInsideBoundary = (hr2.t - hr1.t) * rayLength;
        float hitDistance = negInverseDensity * log(Helpers::RandomFloat());

        if (hitDistance > distanceInsideBoundary)
        {
            return false;
        }

        hr.t = hr1.t + (hitDistance / rayLength);
        hr.point = r.Point(hr.t);

        hr.normal = Vec3(1, 0, 0); // arbitrary
        hr.pMaterial = m_pPhaseFunction;
        
        return true;
    }

    virtual bool BoundingBox(float t0, float t1, AABB& outBox) const override
    {
        return m_pBoundary->BoundingBox(t0, t1, outBox);
    }

private:
    Hittable* m_pBoundary;
    Material* m_pPhaseFunction;
    float negInverseDensity;

        
};
