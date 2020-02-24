#pragma once
#include <cstdlib>

#define PI 3.1415f

class Helpers
{
public:
    static float RandomFloat()
    {
        return rand() / (RAND_MAX + 1.0f);
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
