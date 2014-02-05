#include "Octree.h"

Octree::Octree(const Vec3D& origin, const Vec3D& halfdim)
 : _origin(origin), _halfdim(halfdim), _data(nullptr)
{
    for (int i = 0; i < 8; ++i)
    {
        _children[i] = nullptr;
    }
}


Octree::Octree(const Octree& other)
 : _origin(other._origin), _halfdim(other._halfdim), _data(other._data)
{
    for (int i = 0; i < 8; ++i)
    {
        _children[i] = other._children[i];
    }
}


Octree::Octree(Octree&& other)
 : _origin(std::move(other._origin)),
   _halfdim(std::move(other._halfdim)),
   _data(other._data)
{
    other._data = nullptr;
    for (int i = 0; i < 8; ++i)
    {
        _children[i] = other._children[i];
        other._children[i] = nullptr;
    }
}


Octree::~Octree()
{
    for (int i = 0; i < 8; ++i)
    {
        delete _children[i];
    }
}


unsigned int Octree::getOctant(const Vec3D& pos)const
{
    unsigned int oct = 0;
    if(pos[0] >= _origin[0]) oct |= 4U;
    if(pos[1] >= _origin[1]) oct |= 2U;
    if(pos[2] >= _origin[2]) oct |= 1U;
    return oct;
}


bool Octree::isLeaf() const
{
    for (int i = 0; i < 8; ++i)
    {
        if (_children[i] != nullptr) return false;
    }
    return true;
}


void Octree::insert(Point* point)
{
    if (isLeaf())
    {
        if (_data == nullptr)
        {
            _data = point;
            return;
        }
        else
        {
            Point* oldPoint = _data;
            _data = nullptr;

            for (int i = 0; i < 8; ++i)
            {
                Vec3D newOrigin = _origin;
                newOrigin[0] += _halfdim[0] * (i & 4 ? 0.5 : - 0.5);
                newOrigin[1] += _halfdim[1] * (i & 2 ? 0.5 : - 0.5);
                newOrigin[2] += _halfdim[2] * (i & 1 ? 0.5 : - 0.5);
                _children[i] = new Octree(newOrigin, _halfdim * 0.5);
            }

            _children[getOctant(oldPoint -> pos)] -> insert(oldPoint);
            _children[getOctant(point -> pos)] -> insert(point);
        }
    }
    else
    {
        int oct = getOctant(point -> pos);
        _children[oct] -> insert(point);
    }
}


void Octree::getPointsInside(
    const Vec3D& bmin,
    const Vec3D& bmax,
    std::vector<Point*>& points) const
{
    if (isLeaf())
    {
        if (_data != nullptr)
        {
            const Vec3D& p = _data -> pos;
            if( p[0] > bmax[0] ||
                p[1] > bmax[1] ||
                p[2] > bmax[2]) return;
            
            if( p[0] < bmin[0] ||
                p[1] < bmin[1] ||
                p[2] < bmin[2]) return;
            
            points.push_back(_data);
        }
    }
    else
    {
        for (int i = 0; i < 8; ++i)
        {
            Vec3D cmax = _children[i] -> _origin + _children[i] -> _halfdim;
            Vec3D cmin = _children[i] -> _origin - _children[i] -> _halfdim;

            if( cmax[0] < bmin[0] || 
                cmax[1] < bmin[1] || 
                cmax[1] < bmin[1] ) continue;
            
            if( cmin[0] > bmax[0] ||
                cmin[1] > bmax[1] ||
                cmin[1] > bmax[1] ) continue;

            _children[i] -> getPointsInside(bmin, bmax, points);
        }
    }
}
