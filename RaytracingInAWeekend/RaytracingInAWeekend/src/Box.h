#pragma once

#include "Hittable.h"
#include "XYRect.h"
#include "XZRect.h"
#include "YZRect.h"

class Box : public Hittable 
{
public:
    Box() {}
    ~Box() 
    { 
        delete m_pList;
    }

    Box(const Vec3& p0, const Vec3& p1, Material* pM) : 
        m_Min(p0), m_Max(p1)
    {
        Hittable** list = new Hittable*[6];

        //list[0] = new XYRect(
        //    m_Min.X(), m_Max.X(),
        //    m_Min.Y(), m_Max.Y(),
        //    m_Max.Z(), pM);
        //
        //list[1] = new FlipNormals(new XYRect(
        //    m_Min.X(), m_Max.X(),
        //    m_Min.Y(), m_Max.Y(),
        //    m_Min.Z(), pM));
        //
        //list[2] = new XZRect(
        //    m_Min.X(), m_Max.X(),
        //    m_Min.Z(), m_Max.Z(),
        //    m_Max.Y(), pM);
        //
        //list[3] = new FlipNormals(new XZRect(
        //    m_Min.X(), m_Max.X(),
        //    m_Min.Z(), m_Max.Z(),
        //    m_Min.Y(), pM));
        //
        //list[4] = new YZRect(
        //    m_Min.Y(), m_Max.Y(),
        //    m_Min.Z(), m_Max.Z(),
        //    m_Max.X(), pM);
        //
        //list[5] = new FlipNormals(new YZRect(
        //    m_Min.Y(), m_Max.Y(),
        //    m_Min.Z(), m_Max.Z(),
        //    m_Min.X(), pM));

        list[0] = new XYRect(p0.X(), p1.X(), p0.Y(), p1.Y(), p1.Z(), pM);
        list[1] = new FlipNormals(
            new XYRect(p0.X(), p1.X(), p0.Y(), p1.Y(), p0.Z(), pM));
        list[2] = new XZRect(p0.X(), p1.X(), p0.Z(), p1.Z(), p1.Y(), pM);
        list[3] = new FlipNormals(
            new XZRect(p0.X(), p1.X(), p0.Z(), p1.Z(), p0.Y(), pM));
        list[4] = new YZRect(p0.Y(), p1.Y(), p0.Z(), p1.X(), p1.X(), pM);
        list[5] = new FlipNormals(
            new YZRect(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p0.X(), pM));

        m_pList = new HittableList(list, 6);
    }

    virtual bool Hit(const Ray& r, float t0, float t1, HitRecord& hr) const override
    {
        return m_pList->Hit(r, t0, t1, hr);
    }

    virtual bool BoundingBox(float t0, float t1, AABB& box) const override
    {
        box = AABB(m_Min, m_Max);
        return true;
    }

private:
    Vec3 m_Min;
    Vec3 m_Max;
    Hittable* m_pList;

};

