#include "TutorialParts.h"
#include "Ray.h"
#include "RayFunctions.h"
#include "Sphere.h"
#include <iostream>

void OutputAnImage()
{
    int nx = 200;
    int ny = 100;
    // Header for ppm file 
    // Declare colors are in ascii, with nx cols and ny rows, and the max color is 255
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Vec3 botLeft(-2.0f, -1.0f, -1.0f);
    Vec3 spanHorizontal(4.0f, 0.0f, 0.0f);
    Vec3 spanVertical(0.0f, 2.0f, 0.0f);
    Vec3 origin(0.0f, 0.0f, 0.0f);

    const int kNumObjects = 2;
    Hittable* list[kNumObjects];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5f);
    list[1] = new Sphere(Vec3(0, -100.5f, -1), 100.0f);
    Hittable* pWorld = new HittableList(list, 2);

    // From top to bottom
    for (int j = ny - 1; j >= 0; --j)
    {
        // From left to right
        for (int i = 0; i < nx; ++i)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            Ray r(origin, botLeft + u * spanHorizontal + v * spanVertical);
            Vec3 col = RayFunctions::TestWorld(r, pWorld);
            
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