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

    Ray GetRay(float u, float v) const 
    {
        Vec3 dir = m_BotLeft + u * m_SpanHorizontal + v * m_SpanVertical;
        return Ray(m_Origin, dir);
    }

private:
    Vec3 m_Origin;
    Vec3 m_BotLeft;
    Vec3 m_SpanHorizontal;
    Vec3 m_SpanVertical;
};
