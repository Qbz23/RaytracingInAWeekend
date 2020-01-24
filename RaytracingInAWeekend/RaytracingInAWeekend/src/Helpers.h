#pragma once
#include <cstdlib>

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
};
