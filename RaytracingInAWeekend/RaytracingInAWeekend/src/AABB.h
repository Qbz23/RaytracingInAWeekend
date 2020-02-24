#pragma once

#include "Helpers.h"
#include "Vec3.h"
#include "Ray.h"

class AABB
{
public:
    AABB() {}
    AABB(const Vec3& a, const Vec3& b)
    {
        m_Min = a;
        m_Max = b;
    }

    Vec3 Min() const { return m_Min; } 
    Vec3 Max() const { return m_Max; }

    // Determine whether or not a ray hit the AABB
    inline bool Hit(const Ray& r, float tMin, float tMax) const
    {
        // foreach dimension
        for (int a = 0; a < 3; ++a)
        {
            // calc point at which ray intersects with min and 
            // max on each axis 
            float invD = 1.0f / r.Direction()[a];
            float t0 = (Min()[a] - r.Origin()[a]) * invD;
            float t1 = (Max()[a] - r.Origin()[a]) * invD;

            // If ray going opposite dir in this axis, should flip 
            // min and max, if it hits, it'll hit max first 
            if (invD < 0.0f)
            {
                std::swap(t0, t1);
            }

            // Clamp to tMin and tMax
            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;

            // if tMax less than tMin, it didn't hit on this axis 
            // and it only needs to miss on one axis to miss
            if (tMax <= tMin)
            {
                return false;
            }
        }

        // Hit on all 3 axes, therefore it hit
        return true;
    }

    // Compute the union of two AABB
    static inline AABB SurroundingBox(const AABB& b0, const AABB& b1)
    {
        // Get the min and max of each axis considering both 
        // AABB's to be combined here
        Vec3 bMin(  Helpers::ffMin(b0.Min().X(), b1.Min().X()),
                    Helpers::ffMin(b0.Min().Y(), b1.Min().Y()),
                    Helpers::ffMin(b0.Min().Z(), b1.Min().Z()));
        Vec3 bMax(  Helpers::ffMax(b0.Max().X(), b1.Max().X()),
                    Helpers::ffMax(b0.Max().Y(), b1.Max().Y()),
                    Helpers::ffMax(b0.Max().Z(), b1.Max().Z()));
        return AABB(bMin, bMax);
    }

private:
    Vec3 m_Min;
    Vec3 m_Max;
};