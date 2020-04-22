#pragma once

#include "Hittable.h"

class RotateY : public Hittable
{
public:
    RotateY(Hittable* pHittable, float angle) :
        m_pHittable(pHittable), m_Angle(angle) 
    {
        float radians = angle * (PI / 180.0f);
        m_SinTheta = sin(radians);
        m_CosTheta = cos(radians);
        m_bHasBox = m_pHittable->BoundingBox(0.0f, 1.0f, m_Box);
        Vec3 boxMin = m_Box.Min();
        Vec3 boxMax = m_Box.Max();

        Vec3 min(INFINITY, INFINITY, INFINITY);
        Vec3 max(-INFINITY, -INFINITY, -INFINITY);

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    float x = i * boxMax.X() + (1 - i) * boxMin.X();
                    float y = i * boxMax.Y() + (1 - i) * boxMin.Y();
                    float z = i * boxMax.Z() + (1 - i) * boxMin.Z();

                    float newX = m_CosTheta * x + m_SinTheta * z;
                    float newZ = -m_SinTheta * x + m_CosTheta * z;

                    Vec3 checkVec(newX, y, newZ);

                    for (int c = 0; c < 3; ++c)
                    {
                        min[c] = fmin(min[c], checkVec[c]);
                        max[c] = fmax(max[c], checkVec[c]);
                    }
                }
            }
        }
        
        m_Box = AABB(min, max);
    }

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override
    {
        Vec3 rO = r.Origin();
        Vec3 rDir = r.Direction();

        rO[0] = m_CosTheta * r.Origin()[0] - m_SinTheta * r.Origin()[2];
        rO[2] = m_SinTheta * r.Origin()[0] + m_CosTheta * r.Origin()[2];

        rDir[0] = m_CosTheta * r.Direction()[0] - m_SinTheta * r.Direction()[2];
        rDir[2] = m_SinTheta * r.Direction()[0] + m_CosTheta * r.Direction()[2];

        Ray rRotated(rO, rDir, r.Time());

        if (!m_pHittable->Hit(rRotated, tMin, tMax, hr))
        {
            return false;
        }

        Vec3 p = hr.point;
        Vec3 n = hr.normal;


        p[0] = m_CosTheta * hr.point[0] + m_SinTheta * hr.point[2];
        p[2] = -m_SinTheta * hr.point[0] + m_CosTheta * hr.point[2];

        n[0] = m_CosTheta * hr.normal[0] + m_SinTheta * hr.normal[2];
        n[2] = -m_SinTheta * hr.normal[0] + m_CosTheta * hr.normal[2];

        hr.point = p;
        hr.normal = n;

        hr.SetFaceNormal(rRotated, n);

        return true;
    }

    virtual bool BoundingBox(float t0, float t1, AABB& outBox) const override
    {
        outBox = m_Box; 
        return m_bHasBox;
    }

private:
    Hittable* m_pHittable;
    const float m_Angle;
    bool m_bHasBox;
    AABB m_Box;
    float m_CosTheta;
    float m_SinTheta;
};
