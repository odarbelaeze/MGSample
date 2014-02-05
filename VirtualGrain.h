#ifndef VIRTUAL_GRAIN_H_
#define VIRTUAL_GRAIN_H_

#include "Vec3D.h"
#include "Atom.h"

#include <stack>
#include <vector>
#include <algorithm>
#include <functional>

class VirtualGrain
{
public:
    VirtualGrain(const Vec3D&, size_t);
    ~VirtualGrain();

    Atom pop();
    
    Vec3D getOrigin() const;
    Vec3D getA() const;
    Vec3D getB() const;
    Vec3D getC() const;


private:
    int _id;
    std::stack<Atom> _atoms;

    Vec3D _origin;
    Vec3D _a;
    Vec3D _b;
    Vec3D _c;

    static int _gid;
};

#endif