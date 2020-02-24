#include "TutorialParts.h"
#include "Ray.h"
#include "RayFunctions.h"
#include "Sphere.h"
#include "Helpers.h"
#include "Camera.h"
#include "RandomScene.h"
#include <iostream>

void OutputAnImage()
{
    int nx = 200;
    int ny = 100;
    int ns = 100; // num samples
    // Header for ppm file 
    // Declare colors are in ascii, with nx cols and ny rows, and the max color is 255
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Hittable* pWorld = RandomScene();

    Vec3 lookFrom(13, 2, 3);
    Vec3 lookAt(0, 0, 0);
    float distanceToFocus = 10.0f;
    float aperture = 0.1f;
    Camera cam = Camera(
        lookFrom,               // lookFrom
        lookAt,                 // lookAt
        Vec3(0, 1, 0),          // up
        20.0f,                  // vFov
        float(nx) / float(ny),  // aspect
        aperture,               // aperture
        distanceToFocus         // distance to focus
    );

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
    delete pWorld;
}