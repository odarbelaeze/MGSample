#ifndef VIRTUAL_GRAIN_H_
#define VIRTUAL_GRAIN_H_

#include "Vec3D.h"
#include "Atom.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class VirtualGrain
{
public:
    VirtualGrain(const Vec3D&, int);
    ~VirtualGrain();

    Atom top() const;
    Atom* pop();
    bool isEmpty() const;
    double currentDist() const;
    
    Vec3D getOrigin() const;
    Vec3D getA() const;
    Vec3D getB() const;
    Vec3D getC() const;

    friend std::ostream& operator<< (std::ostream& os, const VirtualGrain& vg);

private:
    int _id;
    std::vector<Atom> _atoms;
    int _head;

    Vec3D _origin;
    Vec3D _a;
    Vec3D _b;
    Vec3D _c;

    static int _gid;
};


#endif