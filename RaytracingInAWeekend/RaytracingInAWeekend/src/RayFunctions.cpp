#include "RayFunctions.h"

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
// Below function solves that quadratic equation, returning true if the resulting 
// discriminant > 0, which means the ray sphere intersection eqn has 2 solutions 
// which implies the ray intersected the sphere
//
bool RayFunctions::HitSphere(const Vec3& center, float radius, const Ray& r)
{
    Vec3 oc = r.Origin() - center;
    float a = Dot(r.Direction(), r.Direction());
    float b = 2.0f * Dot(r.Direction(), oc);
    float c = Dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

Vec3 RayFunctions::TestSphere(const Ray& r)
{
    if (HitSphere(
        Vec3(0, 0, -1), // center
        0.5f,           // radius
        r))             // ray
    {
        return Vec3(1.0f, 0.0f, 0.0f);
    }
    else
    {
        return BackgroundColor(r);
    }
}
       