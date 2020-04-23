#pragma once

#include "Hittable.h"
#include "Texture.h"
#include "Sphere.h"
#include "DiffuseLight.h"
#include "XYRect.h"
#include "XZRect.h"
#include "YZRect.h"
#include "Box.h"
#include "Rotate.h"
#include "Translate.h"
#include "ConstantMedium.h"

Hittable* SimpleLight()
{
    Hittable** hittableArray = new Hittable*[4];

    float floorScale = 1000.0f;
    Vec3 floorCenter = Vec3(0, -floorScale, 0);
    hittableArray[0] = new Sphere(
        floorCenter,
        floorCenter,
        floorScale,
        new Lambertian(new NoiseTexture(4)));

    float sphereScale = 2.0f;
    Vec3 sphereCenter = Vec3(0.f, sphereScale, 0.f);
    hittableArray[1] = new Sphere(
        sphereCenter,
        sphereCenter,
        sphereScale,
        new Lambertian(new NoiseTexture(4)));
    
    float lightIntensity = 4.0f;
    Vec3 emitColor = Vec3(lightIntensity, lightIntensity, lightIntensity);
    Vec3 sphereLightCenter = Vec3(0, 5 + sphereScale, 0);
    hittableArray[2] = new Sphere(
        sphereLightCenter,
        sphereLightCenter,
        sphereScale,
        new DiffuseLight(new ConstantTexture(0.1f * emitColor))
    );

    hittableArray[3] = new XYRect(
        3, 5, // x
        1, 3, // y
        -2,   // z 
        new DiffuseLight(new ConstantTexture(emitColor))
    );

    return new HittableList(hittableArray, 4);
}

Hittable* CornellBox()
{
    const int numHittable = 8;
    Hittable** list = new Hittable*[numHittable];
    int i = 0;

    // left wall
    list[i++] = new FlipNormals(new YZRect(0, 555, 0, 555, 555,
        new Lambertian(new ConstantTexture(Vec3(0.12f, 0.45f, 0.125f)))));
    // right wall
    list[i++] = new YZRect(0, 555, 0, 555, 0,
        new Lambertian(new ConstantTexture(Vec3(0.65f, 0.05f, 0.05f))));
    // light
    list[i++] = new XZRect(213, 343, 227, 332, 554,
        new DiffuseLight(new ConstantTexture(Vec3(15.f, 15.f, 15.f))));
    // floor
    list[i++] = new XZRect(0, 555, 0, 555, 0,
        new Lambertian(new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f))));
    // ceiling
    list[i++] = new FlipNormals(new XZRect(0, 555, 0, 555, 555,
        new Lambertian(new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f)))));
    // back wall
    list[i++] = new FlipNormals(new XYRect(0, 555, 0, 555, 555,
        new Lambertian(new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f)))));
    // boxes 
    Hittable* pBox1 = new Box(
        Vec3(0, 0, 0),
        Vec3(165, 330, 165),
        new Lambertian(new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f))));
    pBox1 = new RotateY(pBox1, 15.0f);
    pBox1 = new Translate(pBox1, Vec3(265, 0, 295));
    list[i++] = pBox1;

    Hittable* pBox2 =
        new ConstantMedium(
            new Box(
                Vec3(0, 0, 0),
                Vec3(165, 165, 165),
                new Lambertian(new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f)))),
            0.01f,
            new ConstantTexture(Vec3(1.0f, 0.0f, 1.0f)));

    pBox2 = new RotateY(pBox2, -18.f);
    pBox2 = new Translate(pBox2, Vec3(130, 0, 65));
    list[i++] = pBox2;

    return new BVHNode(list, i, 0.f, 1.0f);
}

Hittable* FinalScene()
{
    const int boxesPerSide = 20;
    const int numGroundBoxes = boxesPerSide * boxesPerSide;
    const int numSmallSpheres = 1000.0f;
    // 
    // Light, 2 fogs, 1 fog boundary, Moving Sphere, Dialectirc Sphere, Metal Sphere, Earth
    //
    const int numOtherObjects = 8;
    Hittable** objects = new Hittable*[numGroundBoxes + numOtherObjects];
    for (int i = 0; i < boxesPerSide; ++i)
    {
        for (int j = 0; j < boxesPerSide; ++j)
        {
            float w = 100.0f;
            float x0 = -1000.0f + i * w;
            float z0 = -1000.0f + j * w;
            float x1 = x0 + w;
            float y1 = Helpers::RandomFloat() * 100 + 1.0f;
            float z1 = z0 + w;

            //Hittable* pBox = new Box(Vec3(0, 0, 0), Vec3(w, y1, w),
            //    new Lambertian(new ConstantTexture(Vec3(0.48f, 0.83f, 0.53f))));
            //pBox = new Translate(pBox, Vec3(x, 0, z));
            Hittable* pBox = new Box(Vec3(x0, 0, z0), Vec3(x1, y1, z1),
                new Lambertian(new ConstantTexture(Vec3(0.48f, 0.83f, 0.53f))));
            objects[i * boxesPerSide + j] = pBox;
        }
    }

    DiffuseLight* pDiffuseLight = new DiffuseLight(new ConstantTexture(Vec3(1.0f, 1.0f, 1.0f)));
    objects[numGroundBoxes] = new XZRect(123.0f, 423.0f, 147.0f, 412.0f, 554.0f, pDiffuseLight);
   
    Sphere* pBoundaryOuterFog = new Sphere(
        Vec3(0, 0, 0),
        Vec3(0, 0, 0),
        5000.0f,
        new Dielectric(1.5f));
    ConstantMedium* pOuterFog = new ConstantMedium(
        pBoundaryOuterFog,
        0.00005f,
        new ConstantTexture(Vec3(1.0f, 1.0f, 1.0f)));
    objects[numGroundBoxes + 1] = pOuterFog;

    Sphere* pBoundaryInnerFog = new Sphere(
        Vec3(360, 150, 145),
        Vec3(360, 150, 145),
        70.0f,
        new Dielectric(1.5f));
    ConstantMedium* pInnerFog = new ConstantMedium(
        pBoundaryInnerFog,
        0.2f,
        new ConstantTexture(Vec3(0.2f, 0.4f, 0.9f)));
    objects[numGroundBoxes + 2] = pBoundaryInnerFog;
    objects[numGroundBoxes + 3] = pInnerFog;

    Sphere* pMovingSphere = new Sphere(
        Vec3(400, 400, 200),
        Vec3(400, 350, 200),
        50.0f,
        new Lambertian(
            new ConstantTexture(Vec3(0.7f, 0.3f, 0.1f))));
    objects[numGroundBoxes + 4] = pMovingSphere;

    Sphere* pDielectricSphere = new Sphere(
        Vec3(260, 150, 45),
        Vec3(260, 150, 45),
        50,
        new Dielectric(1.5f));
    objects[numGroundBoxes + 5] = pDielectricSphere;
    
    Sphere* pMetalSphere = new Sphere(
        Vec3(0, 150, 145),
        Vec3(0, 150, 145),
        50.0f,
        new Metal(Vec3(0.8f, 0.8f, 0.9f), 10.0f));
    objects[numGroundBoxes + 6] = pMetalSphere;

    Sphere* pEarthSphere = new Sphere(
        Vec3(400, 200, 400),
        Vec3(400, 200, 400),
        100.0f,
        new Lambertian(new ImageTexture("Assets/earthmap.jpg")));
    objects[numGroundBoxes + 7] = pEarthSphere;

    return new BVHNode(objects, numGroundBoxes + numOtherObjects, 0.0f, 1.0f);
}
