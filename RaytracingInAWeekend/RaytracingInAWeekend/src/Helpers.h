#pragma once
#include <cstdlib>

#define PI 3.1415f

class Helpers
{
public:
    // Without worrying about exceptional cases like nan 
    // can be a bit faster than fmin/max, which matters 
    // when this will be called hundreds of thousands, 
    // maybe millions of times
    static inline float ffMin(float a, float b) { return a < b ? a : b; }
    static inline float ffMax(float a, float b) { return a > b ? a : b; }

    static float RandomFloat()
    {
        return rand() / (RAND_MAX + 1.0f);
    }

    static Vec3 RandomVecInUnitDisk()
    {
        Vec3 p;
        do
        {
            p = 2.0*Vec3(Helpers::RandomFloat(), Helpers::RandomFloat(), 0) - Vec3(1, 1, 0);
        } while (Dot(p, p) >= 1.0);
        return p;
    }

    static Vec3 RandomPointInUnitSphere()
    {
        Vec3 p;
        do
        {
            Vec3 randVec = Vec3(RandomFloat(), RandomFloat(), RandomFloat());
            p = 2.0f * randVec - Vec3(1, 1, 1);
        } while (p.SquaredLength() >= 1.0f);
        return p;
    }

    static float Schlick(float cos, float refractionIndex)
    {
        float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * pow((1 - cos), 5);
    }
};
