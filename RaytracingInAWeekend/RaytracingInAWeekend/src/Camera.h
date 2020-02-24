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

    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, float vFov, float aspect)
    {
        Vec3 u, v, w;
        float theta = vFov * PI / 180.0f;
        float halfHeight = tan(theta / 2.0f);
        float halfWidth = aspect * halfHeight;
        m_Origin = lookFrom;
        w = (lookFrom - lookAt).GetNormalized();
        u = Cross(up, w).GetNormalized();
        v = Cross(w, u);
        m_BotLeft = m_Origin - halfWidth * u - halfHeight * v - w;
        m_SpanHorizontal = 2 * halfWidth * u;
        m_SpanVertical = 2 * halfHeight * v;
    }

    Ray GetRay(float u, float v) const 
    {
        Vec3 dir = m_BotLeft + u * m_SpanHorizontal + v * m_SpanVertical - m_Origin;
        return Ray(m_Origin, dir);
    }

private:
    Vec3 m_Origin;
    Vec3 m_BotLeft;
    Vec3 m_SpanHorizontal;
    Vec3 m_SpanVertical;
};
