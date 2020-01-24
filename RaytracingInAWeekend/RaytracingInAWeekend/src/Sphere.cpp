#include "Sphere.h"

//
// See RayFunctions::HitSphere for explanation of underlying math 
// This won't exactly match bc some things are simplified 
//
bool Sphere::Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const
{
    Vec3 oc = r.Origin() - m_Center;
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
            hr.normal = (hr.point - m_Center) / m_Radius;
            return true;
        }
        // If t out of range, try other solution (+ sqrt)
        t = (-b + sqrt(discriminant)) / a;
        if (t < tMax && t > tMin)
        {
            hr.t = t;
            hr.point = r.Point(t);
            hr.normal = (hr.point - m_Center) / m_Radius;
            return true;
        }
    }
    
    return false;
}
