#pragma once

#include "Vec3.h"

class Texture
{
public:
    virtual Vec3 Value(float u, float v, const Vec3& p) const = 0;
};

class ConstantTexture : public Texture
{
public:
    ConstantTexture() {}
    ConstantTexture(Vec3 c) : m_Color(c) {}

    virtual Vec3 Value(float u, float v, const Vec3& p) const override
    {
        // no need for using coordinates u or v, 
        // the entire texture is the same color
        return m_Color;
    }

private:
    Vec3 m_Color;
};

class CheckerTexture : public Texture
{
public:
    CheckerTexture() {}
    CheckerTexture(Texture* pt0, Texture* pt1) : m_pEvenTex(pt0), m_pOddTex(pt1) {}

    virtual Vec3 Value(float u, float v, const Vec3& p) const override
    {
        float sines = sin(10.0f * p.X()) * sin(10.0f * p.Y()) * sin(10.0f * p.Z());
        return sines < 0.0f ? m_pOddTex->Value(u, v, p) : m_pEvenTex->Value(u, v, p);
    }

private:
    Texture* m_pEvenTex;
    Texture* m_pOddTex;
};