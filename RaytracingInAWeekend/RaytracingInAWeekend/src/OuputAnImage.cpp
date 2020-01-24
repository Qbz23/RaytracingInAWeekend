#include "TutorialParts.h"
#include "Vec3.h"
#include <iostream>

void OutputAnImage()
{
    int nx = 200;
    int ny = 100;
    // Header for ppm file 
    // Declare colors are in ascii, with nx cols and ny rows, and the max color is 255
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // From top to bottom
    for (int j = ny - 1; j >= 0; --j)
    {
        // From left to right
        for (int i = 0; i < nx; ++i)
        {
            // Should be a gradient across R and G
            Vec3 col = Vec3(
                float(i) / float(nx),
                float(j) / float(ny),
                0.2f    
            );
            
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
}