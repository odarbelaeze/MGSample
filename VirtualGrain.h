#ifndef VIRTUAL_GRAIN_H_
#define VIRTUAL_GRAIN_H_

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "Atom.h"

typedef Eigen::Vector3d Vec3D;

class VirtualGrain
{
public:
    VirtualGrain(int, int);
    VirtualGrain(const std::vector<Vec3D>&, int, int);

    Vec3D top(int) const;
    Vec3D pop(int);
    bool isEmpty(int) const;
    double currentDist(int) const;

private:
    std::vector<Vec3D> _positions;
    std::vector<int>   _heads;

};


#endif