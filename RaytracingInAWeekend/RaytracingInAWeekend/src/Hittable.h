#pragma once
#include "Ray.h"
#include "AABB.h"

class Material;

struct HitRecord
{
    float t;
    Vec3 point;
    Vec3 normal;
    Material* pMaterial;
    float u;
    float v;
};

class Hittable
{
public:
    virtual ~Hittable() {}
    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& record) const = 0;
    virtual bool BoundingBox(float t0, float t1, AABB& box) const = 0;
};

class FlipNormals : public Hittable
{
public:
    FlipNormals(Hittable* pH) : m_pHittable(pH) {}
    ~FlipNormals() { delete m_pHittable; }

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& hr) const override
    {
        if (m_pHittable->Hit(r, tMin, tMax, hr))
        {
            hr.normal = -hr.normal;
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual bool BoundingBox(float t0, float t1, AABB& box) const override
    {
        return m_pHittable->BoundingBox(t0, t1, box);
    }

private:
    Hittable* m_pHittable;
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
    ~HittableList()
    {
        for (int i = 0; i < m_Size; ++i)
        {
            delete m_List[i];
        }
    }

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& record) const override
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

    virtual bool BoundingBox(float t0, float t1, AABB& box) const override
    {
        if(m_Size < 1)
        {
            return false;
        }

        AABB temp;
        bool firstTrue = m_List[0]->BoundingBox(t0, t1, temp);
        if (!firstTrue)
        {
            return false;
        }
        else
        {
            box = temp;
        }

        for (int i = 1; i < m_Size; ++i)
        {
            if (m_List[i]->BoundingBox(t0, t1, temp))
            {
                box = AABB::SurroundingBox(box, temp);
            }
            else
            {
                return false;
            }
        }

        return true;
    }

private:
    Hittable** m_List;
    int m_Size;
};
