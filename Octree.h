#ifndef OCTREE_H_
#define OCTREE_H_

#include <vector>
#include "Vec3D.h"


struct Point
{
    Vec3D pos;
    int grainId;
};


class Octree
{

public:
    Octree(const Vec3D&, const Vec3D&);
    Octree(const Octree&);
    Octree(Octree&&);
    ~Octree();

    unsigned int getOctant(const Vec3D&)const;
    bool isLeaf() const;
    void insert(Point* point);
    void getPointsInside(
        const Vec3D&,
        const Vec3D&,
        std::vector<Point*>&) const;

private:
    Vec3D _origin;
    Vec3D _halfdim;
    Point* _data;
    Octree* _children[8];

};

#endif