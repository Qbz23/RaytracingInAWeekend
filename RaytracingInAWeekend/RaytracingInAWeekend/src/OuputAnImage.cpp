#include "TutorialParts.h"
#include "Ray.h"
#include "RayFunctions.h"
#include "Sphere.h"
#include "Helpers.h"
#include "Camera.h"
#include <iostream>

void OutputAnImage()
{
    int nx = 200;
    int ny = 100;
    int ns = 500; // num samples
    // Header for ppm file 
    // Declare colors are in ascii, with nx cols and ny rows, and the max color is 255
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    const int kNumObjects = 5;
    Hittable* list[kNumObjects];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5f, new Lambertian(Vec3(0.1f, 0.2f, 0.5f)));
    list[1] = new Sphere(Vec3(0, -100.5f, -1), 100.0f, new Lambertian(Vec3(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.0f));
    // negative normal for dielectric makes it like a bubble with normal pointed inward
    list[3] = new Sphere(Vec3(-1, 0, -1), 0.5f, new Dielectric(1.5f));
    list[4] = new Sphere(Vec3(-1, 0, -1), -0.45f, new Dielectric(1.5f));
    Hittable* pWorld = new HittableList(list, kNumObjects);

    Camera cam;
    // From top to bottom
    for (int j = ny - 1; j >= 0; --j)
    {
        // From left to right
        for (int i = 0; i < nx; ++i)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            Vec3 col(0.0f, 0.0f, 0.0f);
            // Sample a random kernel around expected point for antialiasing
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + Helpers::RandomFloat()) / float(nx);
                float v = float(j + Helpers::RandomFloat()) / float(ny);
                Ray r = cam.GetRay(u, v);
                col += RayFunctions::GetColor(r, pWorld, 0);
            }
            col /= float(ns);
            // take sqrt to gamma correct 
            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            // convert to int 
            const float floatToInt = 255.99f;
            int ir = int(floatToInt * col.R());
            int ig = int(floatToInt * col.G());
            int ib = int(floatToInt * col.B());
            // write color 
            std::cout << ir << " " << ig << " " << ib << "\n";
            // Redirect output to file to output
        }
    }

    // cleanup
    for (int i = 0; i < kNumObjects; ++i)
    {
        delete list[i];
    }
    delete pWorld;
}