#pragma once

#include "Vec3.h"
#include "Helpers.h"

class Perlin
{
public:
    inline float Interp(Vec3 c[2][2][2], float u, float v, float w) const
    {
        float uu = u * u * (3 - 2 * u);
        float vv = v * v * (3 - 2 * v);
        float ww = w * w * (3 - 2 * w);
        float accum = 0;
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 2; ++k) 
                {
                    Vec3 weight_v(u - i, v - j, w - k);
                    accum +=    (i*uu + (1 - i)*(1 - uu))*
                                (j*vv + (1 - j)*(1 - vv))*
                                (k*ww + (1 - k)*(1 - ww))*Dot(c[i][j][k], weight_v);
                }
            }
        }

        return accum;
    }

    float Noise(const Vec3& p) const
    {
        int i = (int)floor(p.X());
        int j = (int)floor(p.Y());
        int k = (int)floor(p.Z());

        float u = p.X() - i;
        float v = p.Y() - j;
        float w = p.Z() - k;

        Vec3 c[2][2][2];
        for (int di = 0; di < 2; ++di)
        {
            for (int dj = 0; dj < 2; ++dj)
            {
                for (int dk = 0; dk < 2; ++dk)
                {
                    c[di][dj][dk] =
                        s_RandomVecs[
                            s_PermX[(i + di) & 255] ^
                            s_PermY[(j + dj) & 255] ^
                            s_PermZ[(k + dk) & 255]
                        ];
                }
            }
        }
            
        return Interp(c, u, v, w);
    }

    float Turb(const Vec3& p, int depth = 7) const
    {
        float accum = 0.0f;
        Vec3 temp = p;
        float weight = 1.0f;
        for (int i = 0; i < depth; ++i)
        {
            accum += weight * Noise(temp);
            weight *= 0.5f;
            temp *= 2.0f;
        }

        return fabs(accum);
    }

    static Vec3* s_RandomVecs;
    static int* s_PermX;
    static int* s_PermY;
    static int* s_PermZ;

    static Vec3* Generate()
    {
        Vec3 * p = new Vec3[256];
        for (int i = 0; i < 256; ++i)
        {
            float x = 2 * Helpers::RandomFloat() - 1;
            float y = 2 * Helpers::RandomFloat() - 1;
            float z = 2 * Helpers::RandomFloat() - 1;
            p[i] = Vec3(x, y, z).GetNormalized();
        }
        return p;
    }
    
    // Shuffles array p of size n
    static void Permute(int* p, int n)
    {
        for (int i = n - 1; i > 0; --i)
        {
            int target = int(Helpers::RandomFloat() * (i + 1));
            int temp = p[i];
            p[i] = p[target];
            p[target] = temp;
        }
    }

    static int* GeneratePerm()
    {
        int * p = new int[256];
        for (int i = 0; i < 256; ++i)
        {
            p[i] = i;
        }
        Permute(p, 256);
        return p;
    }
};
