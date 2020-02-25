#include "Perlin.h"

Vec3* Perlin::s_RandomVecs = Perlin::Generate();
int* Perlin::s_PermX = Perlin::GeneratePerm();
int* Perlin::s_PermY = Perlin::GeneratePerm();
int* Perlin::s_PermZ = Perlin::GeneratePerm();
