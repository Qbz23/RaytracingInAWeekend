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


