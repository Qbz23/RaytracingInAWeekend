#pragma once
#include "Ray.h"

class Camera
{
public:
    Camera() :
        m_Origin(0.0f, 0.0f, 0.0f),
        m_BotLeft(-2.0f, -1.0f, -1.0f),
        m_SpanHorizontal(4.0f, 0.0f, 0.0f),
        m_SpanVertical(0.0f, 2.0f, 0.0f)
    {}

    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, float vFov, float aspect,
           float aperture, float focusDistance)
    {
        lensRadius = aperture / 2.0f;
        float theta = vFov * PI / 180.0f;
        float halfHeight = tan(theta / 2.0f);
        float halfWidth = aspect * halfHeight;
        m_Origin = lookFrom;
        w = (lookFrom - lookAt).GetNormalized();
        u = Cross(up, w).GetNormalized();
        v = Cross(w, u);
        m_BotLeft = m_Origin 
                  - halfWidth * focusDistance * u 
                  - halfHeight * focusDistance * v 
                  - focusDistance * w;
        m_SpanHorizontal = 2 * halfWidth * focusDistance * u;
        m_SpanVertical = 2 * halfHeight * focusDistance * v;
    }

    Ray GetRay(float s, float t) const 
    {
        Vec3 rd = lensRadius * Helpers::RandomVecInUnitDisk();
        Vec3 offset = u * rd.X() + v * rd.Y();
        return Ray(
            m_Origin + offset,
            m_BotLeft + s * m_SpanHorizontal + t * m_SpanVertical
                - m_Origin - offset
        );
    }

private:
    Vec3 m_Origin;
    Vec3 m_BotLeft;
    Vec3 m_SpanHorizontal;
    Vec3 m_SpanVertical;
    Vec3 u, v, w;
    float lensRadius;
};
