#include "Vec3.h"

Vec3& Vec3::operator+=(const Vec3& v2)
{
    m_Data[0] += v2.m_Data[0];
    m_Data[1] += v2.m_Data[1];
    m_Data[2] += v2.m_Data[2];
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v2)
{
    m_Data[0] -= v2.m_Data[0];
    m_Data[1] -= v2.m_Data[1];
    m_Data[2] -= v2.m_Data[2];
    return *this;
}

Vec3& Vec3::operator*=(const Vec3& v2)
{
    m_Data[0] *= v2.m_Data[0];
    m_Data[1] *= v2.m_Data[1];
    m_Data[2] *= v2.m_Data[2];
    return *this;
}

Vec3& Vec3::operator/=(const Vec3& v2)
{
    m_Data[0] /= v2.m_Data[0];
    m_Data[1] /= v2.m_Data[1];
    m_Data[2] /= v2.m_Data[2];
    return *this;
}

Vec3& Vec3::operator*=(const float t)
{
    m_Data[0] *= t;
    m_Data[1] *= t;
    m_Data[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(const float t)
{
    m_Data[0] /= t;
    m_Data[1] /= t;
    m_Data[2] /= t;
    return *this;
}

inline float Vec3::Length() const
{
    return sqrt(SquaredLength());
}

inline float Vec3::SquaredLength() const
{
    return m_Data[0] * m_Data[0] +
           m_Data[1] * m_Data[1] +
           m_Data[2] * m_Data[2];
}

inline void Vec3::Normalize()
{
    float k = 1.0f / Length();
    (*this) *= k;
}

Vec3 Vec3::GetNormalized() const
{
    float k = 1.0f / Length();
    return k * (*this);
}

inline float Vec3::Dot(const Vec3& other) const
{
    return m_Data[0] * other.m_Data[0] + 
           m_Data[1] * other.m_Data[1] + 
           m_Data[2] * other.m_Data[2];
}

inline Vec3 Vec3::Cross(const Vec3& other) const
{
    return Vec3(
        m_Data[1] * other.m_Data[2] - m_Data[2] * other.m_Data[1],
        m_Data[2] * other.m_Data[0] - m_Data[0] * other.m_Data[2],
        m_Data[0] * other.m_Data[1] - m_Data[1] * other.m_Data[0]
    );
}

Vec3 Vec3::Reflect(const Vec3& other)
{
    return (*this) - 2 * Dot(other) * other;
}

float Dot(const Vec3& lhs, const Vec3& rhs)
{
    return lhs.Dot(rhs);
}

Vec3 Cross(const Vec3& lhs, const Vec3& rhs)
{
    return lhs.Cross(rhs);
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(
        lhs.m_Data[0] + rhs.m_Data[0],
        lhs.m_Data[1] + rhs.m_Data[1],
        lhs.m_Data[2] + rhs.m_Data[2]
    );
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(
        lhs.m_Data[0] - rhs.m_Data[0],
        lhs.m_Data[1] - rhs.m_Data[1],
        lhs.m_Data[2] - rhs.m_Data[2]
    );
}

Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(
        lhs.m_Data[0] * rhs.m_Data[0],
        lhs.m_Data[1] * rhs.m_Data[1],
        lhs.m_Data[2] * rhs.m_Data[2]
    );
}

Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(
        lhs.m_Data[0] / rhs.m_Data[0],
        lhs.m_Data[1] / rhs.m_Data[1],
        lhs.m_Data[2] / rhs.m_Data[2]
    );
}

Vec3 operator+(const Vec3& lhs, float rhs)
{
    return Vec3(
        lhs.m_Data[0] + rhs,
        lhs.m_Data[1] + rhs,
        lhs.m_Data[2] + rhs
    );
}

Vec3 operator+(float lhs, const Vec3& rhs)
{
    return rhs + lhs;
}

Vec3 operator-(const Vec3& lhs, float rhs)
{
    return Vec3(
        lhs.m_Data[0] - rhs,
        lhs.m_Data[1] - rhs,
        lhs.m_Data[2] - rhs
    );
}

Vec3 operator*(const Vec3& lhs, float rhs)
{
    return Vec3(
        lhs.m_Data[0] * rhs,
        lhs.m_Data[1] * rhs,
        lhs.m_Data[2] * rhs
    );
}

Vec3 operator*(float lhs, const Vec3& rhs)
{
    return rhs * lhs;
}

Vec3 operator/(const Vec3& lhs, float rhs)
{
    return Vec3(
        lhs.m_Data[0] / rhs,
        lhs.m_Data[1] / rhs,
        lhs.m_Data[2] / rhs
    );
}

std::ostream& operator<<(std::ostream& os, Vec3& v)
{
    os << v.m_Data[0] << ", " << v.m_Data[1] << ", " << v.m_Data[2];
    return os;
}

std::istream& operator>>(std::istream& is, Vec3& v)
{
    is >> v.m_Data[0] >> v.m_Data[1] >> v.m_Data[2];
    return is;
}