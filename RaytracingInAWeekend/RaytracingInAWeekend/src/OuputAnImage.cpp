#include "TutorialParts.h"

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
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2f;
            // convert to int 
            const float floatToInt = 255.99f;
            int ir = int(floatToInt * r);
            int ig = int(floatToInt * g);
            int ib = int(floatToInt * b);
            // write color 
            std::cout << ir << " " << ig << " " << ib << "\n";
            // Redirect output to file to output
        }
    }
}