#pragma once
#include "Ray.h"

class Material;

struct HitRecord
{
    float t;
    Vec3 point;
    Vec3 normal;
    Material* pMaterial;
};

class Hittable
{
public:
    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& record) const = 0;
};

//
// Store multiple hittable objects, hit function fills out information about the 
// closest hit and returns true if it hit anything
//
class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(Hittable** list, int size) : m_List(list), m_Size(size) {}

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& record) const
    {
        HitRecord hrTemp;
        bool hitSomething = false;
        float closest = tMax;

        for (int i = 0; i < m_Size; ++i)
        {
            if (m_List[i]->Hit(r, tMin, closest, hrTemp))
            {
                hitSomething = true;
                closest = hrTemp.t;
                record = hrTemp;
            }
        }

        return hitSomething;
    }

private:
    Hittable** m_List;
    int m_Size;
};
