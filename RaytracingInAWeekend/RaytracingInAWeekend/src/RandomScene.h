#pragma once

#include "Hittable.h"
#include "Sphere.h"
#include "BVHNode.h"
#include "ImageTexture.h"

Hittable* RandomScene()
{
    int n = 1650;
    Hittable** list = new Hittable*[n + 1];
    
    list[0] = new Sphere(
        Vec3(0, -1000, 0),
        Vec3(0, -1000, 0),
        1000,
        new Lambertian(
            new CheckerTexture(
                new ConstantTexture(
                    Vec3(0.2f, 0.3f, 0.1f)
                ),
                new ConstantTexture(
                    Vec3(0.9f, 0.9f, 0.9f)
                )
            )
        )
    );

    int i = 1;
    for (int a = -20; a < 20; ++a)
    {
        for (int b = -20; b < 20; ++b)
        {
            float chooseMat = Helpers::RandomFloat();
            Vec3 center(
                a + 0.9f * Helpers::RandomFloat(),
                0.2f,
                b + 0.9f * Helpers::RandomFloat()
            );

            if ((center - Vec3(4.0f, 0.2f, 0.0f)).Length() > 0.9f)
            {
                if (chooseMat < 0.8f) // diffuse
                {
                    Texture* pTex;
                    if (chooseMat < 0.25f) // have a subset be noise tex
                    {
                        // [0, 0.25] -> [0, 1]
                        pTex = new NoiseTexture(4 * chooseMat);
                    }
                    else
                    {
                        pTex = new ConstantTexture(
                            Vec3(
                                Helpers::RandomFloat() * Helpers::RandomFloat(),
                                Helpers::RandomFloat() * Helpers::RandomFloat(),
                                Helpers::RandomFloat() * Helpers::RandomFloat()
                            )
                        );
                    }

                    list[i++] =
                        new Sphere(
                            center,
                            // This creates the motion blurred spheres that look 
                            // like theyre falling. Comment out and replace with 
                            // just "center" below to have no motion blur
                            //center + Vec3(0, 0.5f * Helpers::RandomFloat(), 0.0f),
                            center,
                            0.2f,
                            new Lambertian(pTex)
                        );
                }
                else if (chooseMat < 0.95f) // metal
                {
                    list[i++] =
                        new Sphere(
                            center,
                            center,
                            0.2f,
                            new Metal(
                                Vec3(
                                    0.5f * (1 + Helpers::RandomFloat()),
                                    0.5f * (1 + Helpers::RandomFloat()),
                                    0.5f * (1 + Helpers::RandomFloat())
                                ),
                                0.5f * Helpers::RandomFloat()
                            )
                        );
                }
                else // glass
                {
                    list[i++] =
                        new Sphere(
                            center,
                            center,
                            0.2f,
                            new Dielectric(1.5f)
                        );
                }
            }
        }
    }

    list[i++] = new Sphere(
                        Vec3(0.0f, 1.0f, 0.0f), 
                        Vec3(0.0f, 1.0f, 0.0f),
                        1.0f, 
                        new Dielectric(1.5f)
                );
    list[i++] = new Sphere(
                        Vec3(-4.0f, 1.0f, 0.0f), 
                        Vec3(-4.0f, 1.0f, 0.0f),
                        1.0f, 
                        new Lambertian(
                            new ImageTexture("Assets/earthmap.jpg")
                        )
                );
    list[i++] = new Sphere(
                        Vec3(4.0f, 1.0f, 0.0f), 
                        Vec3(4.0f, 1.0f, 0.0f),
                        1.0f, 
                        new Metal(
                            Vec3(0.7f, 0.6f, 0.5f), 
                            0.0f
                        )
                );

    // Can return as a hittable List to run without BVH, but much slower
    //return new HittableList(list, i);
    return new BVHNode(list, i, 0.0f, 1.0f);
}