#pragma once

#include "Vec3.h"
#include "Perlin.h"

class Texture
{
public:
    virtual ~Texture() { }
    virtual Vec3 Value(float u, float v, const Vec3& p) const = 0;
};

class ConstantTexture : public Texture
{
public:
    ConstantTexture() {}
    ConstantTexture(Vec3 c) : m_Color(c) {}
    ~ConstantTexture() {}

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
    CheckerTexture() : m_pEvenTex(nullptr), m_pOddTex(nullptr) {}
    CheckerTexture(Texture* pt0, Texture* pt1) : m_pEvenTex(pt0), m_pOddTex(pt1) {}
    ~CheckerTexture() 
    {
        if (m_pEvenTex)
        {
            delete m_pEvenTex;
        }
        if (m_pOddTex)
        {
            delete m_pOddTex;
        }
    }

    virtual Vec3 Value(float u, float v, const Vec3& p) const override
    {
        float sines = sin(10.0f * p.X()) * sin(10.0f * p.Y()) * sin(10.0f * p.Z());
        return sines < 0.0f ? m_pOddTex->Value(u, v, p) : m_pEvenTex->Value(u, v, p);
    }

private:
    Texture* m_pEvenTex;
    Texture* m_pOddTex;
};

class NoiseTexture : public Texture
{
public:
    NoiseTexture(float scale) : m_Scale(scale) {}
    virtual Vec3 Value(float u, float v, const Vec3& p) const override
    {
        return Vec3(1, 1, 1) * 0.5f * 
                (1 + sin(
                        m_Scale * p.Z() + 10.0f * m_Noise.Turb(p)
                    )
                );
    }

private:
    Perlin m_Noise;
    float m_Scale;
};
