#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Vec3
{
public:
    // ctors
    Vec3() {}
    Vec3(float x, float y, float z) : m_Data{ x, y, z } {}

    // getters
    inline float X() const { return m_Data[0]; }
    inline float Y() const { return m_Data[1]; }
    inline float Z() const { return m_Data[2]; }
    inline float R() const { return m_Data[0]; }
    inline float G() const { return m_Data[1]; }
    inline float B() const { return m_Data[2]; }

    // unary +- 
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-m_Data[0], -m_Data[1], -m_Data[2]); }

    // subscript
    inline float operator[](int i) const { return m_Data[i]; }
    inline float& operator[](int i) { return m_Data[i]; }

    // * equals ops 
    Vec3& operator+=(const Vec3& v2);
    Vec3& operator-=(const Vec3& v2);
    Vec3& operator*=(const Vec3& v2);
    Vec3& operator/=(const Vec3& v2);
    Vec3& operator*=(const float t);
    Vec3& operator/=(const float t);

    // other helpers 
    inline float Length() const;
    inline float SquaredLength() const;
    inline void Normalize(); // inplace version
    Vec3 GetNormalized() const; // return a normalized copy version
    inline float Dot(const Vec3& other) const;
    inline Vec3 Cross(const Vec3& other) const;
    Vec3 Reflect(const Vec3& other);
    bool Refract(const Vec3& normal, float niOverNt, Vec3& refracted);

    // might be useful to have this other calling convention
    friend float Dot(const Vec3& lhs, const Vec3& rhs);
    friend Vec3 Cross(const Vec3& lhs, const Vec3& rhs);

    // binary ops 
    friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
    friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
    friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs);
    friend Vec3 operator/(const Vec3& lhs, const Vec3& rhs);
    friend Vec3 operator+(const Vec3& lhs, float rhs);
    friend Vec3 operator+(float lhs, const Vec3& rhs);
    friend Vec3 operator-(const Vec3& lhs, float rhs);
    friend Vec3 operator*(const Vec3& lhs, float rhs);
    friend Vec3 operator*(float lhs, const Vec3& rhs);
    friend Vec3 operator/(const Vec3& lhs, float rhs);

    // in/out ops
    friend std::ostream& operator<<(std::ostream& os, Vec3& v);
    friend std::istream& operator>>(std::istream& os, Vec3& v);

private:
    float m_Data[3];
};