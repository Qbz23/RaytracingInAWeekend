#pragma once
#include "Ray.h"

class RayFunctions
{
public:
    static Vec3 BackgroundColor(const Ray& ray);

    static bool HitSphere(const Vec3& center, float radius, const Ray& r);
    static Vec3 TestSphere(const Ray& r);
};