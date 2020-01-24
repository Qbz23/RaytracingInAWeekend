#pragma once
#include <cstdlib>

class Helpers
{
public:
    static float RandomFloat()
    {
        return rand() / (RAND_MAX + 1.0f);
    }
};
