#pragma once
#include "Vec3.h"

class Ray
{
public:
    // ctors
    Ray() {}
    Ray(const Vec3& origin, const Vec3& dir) :
        m_Origin(origin), m_Direction(dir) {}

    Vec3 Origin() const { return m_Origin; }
    Vec3 Direction() const { return m_Direction; }
    Vec3 Point(float t) const { return m_Origin + t * m_Direction; }

private:
    Vec3 m_Origin;
    Vec3 m_Direction;
};