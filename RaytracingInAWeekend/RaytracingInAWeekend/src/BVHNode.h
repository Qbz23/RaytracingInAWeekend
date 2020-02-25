#pragma once

#include "Hittable.h"

class BVHNode : public Hittable
{
public:
    BVHNode() {}
    BVHNode(Hittable** l, int n, float t0, float t1);
    ~BVHNode();

    virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& record) const override;
    virtual bool BoundingBox(float t0, float t1, AABB& box) const override;

private:
    Hittable* m_pLeft;
    Hittable* m_pRight;
    AABB m_Box;
};
