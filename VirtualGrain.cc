#include "VirtualGrain.h"

int VirtualGrain::_gid = 0;


VirtualGrain::VirtualGrain(const Vec3D& origin, int size)
 : _id(_gid ++), _origin(origin)
{
    std::vector<Vec3D> basis({ Vec3D(0.0, 0.0, 0.0) });

    _a = randomUnit();
    _b = randomUnit();
    _c = cross(_a, _b);
    _b = cross(_a, _c);

    _b = _b / norm(_b);
    _c = _c / norm(_c);

    for (int i = - size; i <= size; ++i)
    {
        for (int j = - size; j <= size; ++j)
        {
            for (int k = - size; k <= size; ++k)
            {
                for (const Vec3D& pos : basis)
                {
                    _atoms.push_back(Atom(_origin + i * _a + j * _b + k * _c, _id));
                }
            }
        }
    }

    std::sort(begin(_atoms), end(_atoms), 
        [&, this](const Atom& a, const Atom& b) {
            return dist(_origin, a.pos) > dist(_origin, b.pos);
        }
    );

    _head = _atoms.size();

}


VirtualGrain::~VirtualGrain()
{}


Atom* VirtualGrain::pop()
{
    return & _atoms[-- _head];
}


Atom VirtualGrain::top() const
{
    return _atoms[_head - 1];
}


bool VirtualGrain::isEmpty() const
{
    return _head == 1;
}


double VirtualGrain::currentDist() const
{
    return dist(top().pos, _origin);
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


std::ostream& operator<< (std::ostream& os, const VirtualGrain& vg)
{
    for (int i = 0; i < vg._head; ++i)
    {
        os << vg._atoms[i].pos[0] << " " 
           << vg._atoms[i].pos[1] << " "
           << vg._atoms[i].pos[2] << " "
           << vg._atoms[i].gid    << std::endl;
    }
    return os;
}

