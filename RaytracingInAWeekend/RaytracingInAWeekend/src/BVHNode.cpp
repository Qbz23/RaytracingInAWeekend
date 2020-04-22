#include "BVHNode.h"
#include <assert.h>

// Sort by X
int BoxXCompare(const void * a, const void * b)
{
    AABB boxLeft, boxRight;
    Hittable* ah = *(Hittable**)a;
    Hittable* bh = *(Hittable**)b;

    if (!ah->BoundingBox(0, 0, boxLeft) || !bh->BoundingBox(0, 0, boxRight))
    {
        std::cerr << "No bounding box in BVHNode constructor\n";
    }

    if (boxLeft.Min().X() - boxRight.Min().X() < 0.0f)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Sort by Y
int BoxYCompare(const void * a, const void * b)
{
    AABB boxLeft, boxRight;
    Hittable* ah = *(Hittable**)a;
    Hittable* bh = *(Hittable**)b;

    if (!ah->BoundingBox(0, 0, boxLeft) || !bh->BoundingBox(0, 0, boxRight))
    {
        std::cerr << "No bounding box in BVHNode constructor\n";
    }

    if (boxLeft.Min().Y() - boxRight.Min().Y() < 0.0f)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Sort by Z
int BoxZCompare(const void * a, const void * b)
{
    AABB boxLeft, boxRight;
    Hittable* ah = *(Hittable**)a;
    Hittable* bh = *(Hittable**)b;

    if (!ah->BoundingBox(0, 0, boxLeft) || !bh->BoundingBox(0, 0, boxRight))
    {
        std::cerr << "No bounding box in BVHNode constructor\n";
    }

    if (boxLeft.Min().Z() - boxRight.Min().Z() < 0.0f)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Construct BVH tree recursively, first call of this ctor 
// will be to construct the root node
BVHNode::BVHNode(Hittable** l, int n, float t0, float t1)
{
    // Pick a random axis
    int axis = int(3 * Helpers::RandomFloat());

    // Sort the primitives along that axis
    if (axis == 0)
    {
        qsort(l, n, sizeof(Hittable*), BoxXCompare);
    }
    else if (axis == 1)
    {
        qsort(l, n, sizeof(Hittable*), BoxYCompare);
    }
    else
    {
        qsort(l, n, sizeof(Hittable*), BoxZCompare);
    }

    // If only one primitive left, no remaining seperation necessary 
    // both child nodes point to the actual geometry 
    if (n == 1)
    {
        m_pLeft = m_pRight = l[0];
    }
    // If only two primitives left, only need to sperate the two remaining 
    // primitives, each child node will point to one of the remaining primitives
    else if (n == 2)
    {
        m_pLeft = l[0];
        m_pRight = l[1];
    }
    // If more than two primitives left, need to continue creating subtrees
    else
    {
        int half = n / 2;
        // Put the first half of the primitives in left child
        m_pLeft = new BVHNode(l, half, t0, t1);
        // put the second half of the primitives in right child
        m_pRight = new BVHNode(l + half, n - half, t0, t1);
    }

    // Calculate the bounding box of the primitives in each of your child nodes
    AABB boxLeft, boxRight;
    if (!m_pLeft->BoundingBox(t0, t1, boxLeft) ||
        !m_pRight->BoundingBox(t0, t1, boxRight))
    {
        std::cerr << "No bounding Box in BVHNode Constructor\n";
    }

    // Your own bounding box is the union of your children bounding boxes
    m_Box = AABB::SurroundingBox(boxLeft, boxRight);
}

bool BVHNode::Hit(const Ray& r, float tMin, float tMax, HitRecord& record) const
{
    // If hits the union AABB of all geometry in this node
    if (m_Box.Hit(r, tMin, tMax))
    {
        // Check if its hitting 
        HitRecord hrLeft, hrRight;
        bool hitLeft = m_pLeft->Hit(r, tMin, tMax, hrLeft);
        bool hitRight = m_pRight->Hit(r, tMin, tMax, hrRight);

        // If hit both children, use whichever one was hit by the ray 
        // first by checking which one has a lesser t
        if (hitLeft && hitRight)
        {
            record = hrLeft.t < hrRight.t ? hrLeft : hrRight;
            return true;
        }
        else if (hitLeft)
        {
            record = hrLeft;
            return true;
        }
        else if (hitRight)
        {
            record = hrRight;
            return true;
        }
        else
        {
            // Just b/c hit the union bounding box doesnt necssarily 
            // mean hit one of the children bounding boxes
            // Example:
            // ________         ________ 
            // |......|         |......|
            // |..AA..|         |..BB..|    
            // |______|         |______| 
            // _________________________
            // |......           ......|
            // |..AA..           ..BB..| 
            // |_______________________|
            //
            // A ray passing through the middle would hit this node's bounding 
            // box but not either of its children's bounding boxes
            //
            return false;
        }
    }
    else
    {
        return false;
    }
}

BVHNode::~BVHNode()
{
    if (m_pLeft != nullptr)
    {
        //delete m_pLeft;
        //m_pLeft = nullptr;
    }
    if (m_pRight != nullptr)
    {
        //delete m_pRight;
        //m_pRight = nullptr;
    }
}

bool BVHNode::BoundingBox(float t0, float t1, AABB& box) const
{
    box = m_Box;
    return true;
}
