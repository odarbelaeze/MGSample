#ifndef ATOM_H_
#define ATOM_H_

#include <eigen3/Eigen/Dense>

typedef Eigen::Vector3d Vec3D;

struct Atom
{ 
    Vec3D pos;
    int gid;
    Atom(const Vec3D&, int);
};

#endif