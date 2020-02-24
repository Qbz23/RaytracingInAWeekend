#include "Sphere.h"

//
// See RayFunctions::HitSphere for explanation of underlying math 
// This won't exactly match bc some things are simplified 
//
bool Sphere::Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const
{
    Vec3 oc = r.Origin() - Center(r.Time());
    float a = Dot(r.Direction(), r.Direction());
    float b = Dot(r.Direction(), oc);
    float c = Dot(oc, oc) - m_Radius * m_Radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float t = (-b - sqrt(discriminant)) / a;
        if (t < tMax && t > tMin)
        {
            hr.t = t;
            hr.point = r.Point(t);
            hr.normal = (hr.point - Center(r.Time())) / m_Radius;
            hr.pMaterial = m_pMaterial;
            return true;
        }
        // If t out of range, try other solution (+ sqrt)
        t = (-b + sqrt(discriminant)) / a;
        if (t < tMax && t > tMin)
        {
            hr.t = t;
            hr.point = r.Point(t);
            hr.normal = (hr.point - Center(r.Time())) / m_Radius;
            hr.pMaterial = m_pMaterial;
            return true;
        }
    }
    
    return false;
}

bool Sphere::BoundingBox(float t0, float t1, AABB& box) const
{
    const Vec3 radiusVec(m_Radius, m_Radius, m_Radius);
    AABB box0(Center(t0) - radiusVec,
              Center(t0) + radiusVec);
    AABB box1(Center(t1) - radiusVec,
              Center(t1) + radiusVec);
    box = AABB::SurroundingBox(box0, box1);
    return true;
}
