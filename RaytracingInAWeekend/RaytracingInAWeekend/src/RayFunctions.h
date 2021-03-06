#pragma once
#include "Ray.h"
#include "Hittable.h"

class RayFunctions
{
public:
    static Vec3 BackgroundColor(const Ray& ray);

    static float HitSphere(const Vec3& center, float radius, const Ray& r);
    
    static Vec3 GetColor(const Ray& r, Hittable* pWorld, int depth);
};