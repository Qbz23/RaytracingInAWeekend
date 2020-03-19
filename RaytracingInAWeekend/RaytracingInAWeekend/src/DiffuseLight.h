#pragma once

#include "Material.h"

class DiffuseLight : public Material
{
public:
    DiffuseLight(Texture* pT) : m_pTex(pT) {}
    ~DiffuseLight() { if (m_pTex != nullptr) delete m_pTex; }

    virtual bool Scatter(const Ray& rIn, const HitRecord& hr,
        Vec3& attenuation, Ray& scattered) const override
    {
        return false;
    }

    virtual Vec3 Emitted(float u, float v, const Vec3& p)
    {
        return m_pTex->Value(u, v, p);
    }

private:
    Texture* m_pTex = nullptr;
};