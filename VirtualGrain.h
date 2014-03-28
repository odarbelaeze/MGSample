#ifndef VIRTUAL_GRAIN_H_
#define VIRTUAL_GRAIN_H_

#include <algorithm>
#include <cstdlib>
#include <vector>

#include <eigen3/Eigen/Dense>

typedef Eigen::Vector3d Vec3D;

class VirtualGrain
{
public:
    VirtualGrain(const int&, const int&);

    Vec3D top(int) const;
    Vec3D pop(int);

    bool isEmpty(int) const;
    double currentDist(int) const;

    bool available() const;

private:
    std::vector<std::vector<long> > _positions;
    std::vector<long>   _heads;
    long _width;

    std::vector<long> _findNbs(long c);

};


#endif