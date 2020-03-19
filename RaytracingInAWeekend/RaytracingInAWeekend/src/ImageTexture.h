#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

class ImageTexture : public Texture
{
public:
    ImageTexture() {}
    ImageTexture(const char* filename)
    {
        int comp;
        m_pData = stbi_load(filename, &m_Width, &m_Height, &comp, 0);    
    }

    Vec3 Value(float u, float v, const Vec3& p) const override
    {
        int i = (int)(u * m_Width);
        int j = (int)((1.0f - v) * m_Height - 0.001f);
        i = (i < 0 ? 0 : i);
        j = (j < 0 ? 0 : j);
        i = (i > (m_Width - 1) ? m_Width - 1 : i);
        j = (j > (m_Height - 1) ? m_Height - 1 : j);
        int baseIndex = 3 * i + 3 * m_Width * j;
        const float kMaxColor = 255.0f;
        float r = ((int)(m_pData[baseIndex])) / kMaxColor;
        float g = ((int)(m_pData[baseIndex + 1])) / kMaxColor;
        float b = ((int)(m_pData[baseIndex + 2])) / kMaxColor;
        return Vec3(r, g, b);
    }

private:
    unsigned char* m_pData;
    int m_Width;
    int m_Height;
};