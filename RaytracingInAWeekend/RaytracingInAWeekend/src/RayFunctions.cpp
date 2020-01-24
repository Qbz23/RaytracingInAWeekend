#include "RayFunctions.h"
#include "Helpers.h"
#include <limits>

Vec3 RayFunctions::BackgroundColor(const Ray& ray)
{
    Vec3 unitDir = ray.Direction().GetNormalized();
    float t = 0.5f * (unitDir.Y() + 1.0f);
    // Mix light blue and white based on ray Y 
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

//
// Recall sphere at origin is 
//      x^2 + y^2 + z^2 = R^2 
// aka, for any P=(x,y,z), on sphere if above is true
// If the sphere's center is at C, it is instead 
//      (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = R^2
// Note that vector from center C to point P is (P - C)
// therefore we can rewrite our circle eqn 
//      Dot((P-C), (P-C)) = R^2
// Aka, any point P that satisfies above is on sphere 
// We want to find out if our Ray, made up of points defined as 
//      Origin + t * Direction; (future Origin=A, Direction=B)
// Has one or more t's that satisfy the circle eqn 
//      Dot((P(t) - C), (P(t) - C)) = R^2
//      Dot(((A + t * B) - C), ((A + t * B) - C)) = R^2 
// Do some algebra and you'll end up with 
//      t^2 * Dot(B, B) + 2 * t * Dot(B, A-C) + Dot((A-C), (A-C)) - R^2 = 0
// It's a quadratic equation of the form 
//      at^2 + bt + c = 0
// Where terms are the following 
//      a = Dot(B, B)
//      b = 2 * Dot(B, A-C)
//      c = Dot((A-C), (A-C)) - R^2
// Below function solves that quadratic equation, returning the T value 
// of the ray's first intersection with the sphere or -1 if no intersection
//
float RayFunctions::HitSphere(const Vec3& center, float radius, const Ray& r)
{
    Vec3 oc = r.Origin() - center;
    float a = Dot(r.Direction(), r.Direction());
    float b = 2.0f * Dot(r.Direction(), oc);
    float c = Dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0f;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

Vec3 RayFunctions::GetColor(const Ray& r, Hittable* pWorld)
{
    HitRecord hr;
    if (pWorld->Hit(r, 0.001f, std::numeric_limits<float>::max(), hr))
    {
        // Pick a random direction to bounce towards 
        Vec3 target = hr.point + hr.normal + Helpers::RandomPointInUnitSphere();
        // Accumulate 50% of the color of each ray bounce
        return 0.5f * GetColor(Ray(hr.point, target - hr.point), pWorld);
    }
    else
    {
        return BackgroundColor(r);
    }
}
       