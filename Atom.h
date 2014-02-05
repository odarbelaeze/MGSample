#ifndef ATOM_H_
#define ATOM_H_

#include "Vec3D.h"

struct Atom
{ 
    Vec3D pos;
    int gid;
    Atom(const Vec3D&, int);
};

#endif