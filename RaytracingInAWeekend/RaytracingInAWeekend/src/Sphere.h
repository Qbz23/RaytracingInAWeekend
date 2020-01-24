#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere() {};
    Sphere(Vec3 center, float r) : m_Center(center), m_Radius(r) {}
    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override;

private:
    Vec3 m_Center;
    float m_Radius;
};
