#include "VirtualGrain.h"

int VirtualGrain::_gid = 0;


VirtualGrain::VirtualGrain(const Vec3D& origin, size_t size)
 : _id(_gid ++), _origin(origin)
{
    std::vector<Vec3D> basis({ Vec3D(0.0, 0.0, 0.0) });

    for (int i = - size; i <= size; ++i)
    {
        for (int j = - size; j <= size; ++j)
        {
            for (int k = - size; k <= size; ++k)
            {
                for (const Vec3D& pos : basis)
                {
                    _atoms.push(Atom( i * _a + j * _b + k * _c, _id));
                }
            }
        }
    }

    std::sort(begin(_atoms), end(_atoms), 
        [&_origin](const Vec3D& a, const Vec3D& b) {
            return distance(_origin, a) < distance(_origin, b);
        }
    );
}


VirtualGrain::~VirtualGrain()
{}


Atom VirtualGrain::pop()
{
    return _atoms.pop();
}


Vec3D VirtualGrain::getOrigin() const
{
    return _origin;
}


Vec3D VirtualGrain::getA() const
{
    return _a;
}


Vec3D VirtualGrain::getB() const
{
    return _b;
}


Vec3D VirtualGrain::getC() const
{
    return _c;
}



