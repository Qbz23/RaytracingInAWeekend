#include "RayFunctions.h"

Vec3 RayFunctions::BackgroundColor(const Ray& ray)
{
    Vec3 unitDir = ray.Direction().GetNormalized();
    float t = 0.5f * (unitDir.Y() + 1.0f);
    // Mix light blue and white based on ray Y 
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}
