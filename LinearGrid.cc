#include "LinearGrid.h"

LinearGrid::LinearGrid (
    const Vec3D& origin,
    const Vec3D& halfwidth,
    const Vec3D& cell
)
    :   _origin(origin),
        _halfwidth(halfwidth),
        _cell(cell)
{
    Vec3D dims = 2.0 * halfwidth.array() / cell.array();

    _w = std::fmod(dims(0), 1.0) == 0.0 ? (int) dims(0) : (int) dims(0) + 1;
    _l = std::fmod(dims(1), 1.0) == 0.0 ? (int) dims(1) : (int) dims(1) + 1;
    _h = std::fmod(dims(2), 1.0) == 0.0 ? (int) dims(2) : (int) dims(2) + 1;

    _data.resize(_w * _l * _h);
}



LinearGrid::LinearGrid (const Vec3D& origin, const Vec3D& halfwidth, double l)
    :   _origin(origin),
        _halfwidth(halfwidth),
        _cell(l, l, l)
{
    Vec3D dims = 2.0 * halfwidth.array() / _cell.array();

    _w = std::fmod(dims(0), 1.0) == 0.0 ? (int) dims(0) : (int) dims(0) + 1;
    _l = std::fmod(dims(1), 1.0) == 0.0 ? (int) dims(1) : (int) dims(1) + 1;
    _h = std::fmod(dims(2), 1.0) == 0.0 ? (int) dims(2) : (int) dims(2) + 1;

    _data.resize(_w * _l * _h);
}


void LinearGrid::insert(Point* point)
{
    _data.at(getCell(point -> pos)).push_back(point);
}


int LinearGrid::getCell (const Vec3D& pos) const
{
    Vec3D dims = ((pos - _origin) + _halfwidth).array() / _cell.array();
    return (int) dims(0) + (int) dims(1) * _w + (int) dims(2) * _w * _l;
}


int LinearGrid::getCell (int i, int j, int k) const
{
    return i + j * _w + k * _w * _l;
}


void LinearGrid::findInBox (
    const Vec3D& aa, 
    const Vec3D& bb, 
    std::vector<Point*>& query
) const
{
    assert((aa.array() < bb.array()).minCoeff() == 1);
    
    int ida = getCell(aa);
    int idb = getCell(bb);
    
    int i_min = (ida % _w);
    int j_min = (ida / _w) % _l;
    int k_min = (ida / _w / _l);

    int i_max = (idb % _w);
    int j_max = (idb / _w) % _l;
    int k_max = (idb / _w / _l);

    for (int i = i_min; i <= i_max; ++i)
    {
        for (int j = j_min; j <= j_max; ++j)
        {
            for (int k = k_min; k <= k_max; ++k)
            {
                for (auto&& pointptr : _data.at(getCell(i, j, k)))
                {
                    if (((pointptr -> pos).array() >= aa.array()).minCoeff() &&
                        ((pointptr -> pos).array() <= bb.array()).minCoeff())
                    {
                        query.push_back(pointptr);
                    }
                }
            }
        }
    }

}


void LinearGrid::findInSphere (
    const Vec3D& center,
    double radius,
    std::vector<Point*>& query
) const
{
    assert(radius > 0.0);

    int ida = getCell(center.array() - radius);
    int idb = getCell(center.array() + radius);
    
    int i_min = (ida % _w);
    int j_min = (ida / _w) % _l;
    int k_min = (ida / _w / _l);

    int i_max = (idb % _w);
    int j_max = (idb / _w) % _l;
    int k_max = (idb / _w / _l);

    for (int i = i_min; i <= i_max; ++i)
    {
        for (int j = j_min; j <= j_max; ++j)
        {
            for (int k = k_min; k <= k_max; ++k)
            {
                for (auto&& pointptr : _data.at(getCell(i, j, k)))
                {
                    if ((pointptr -> pos - center).norm() < radius)
                    {
                        query.push_back(pointptr);
                    }
                }
            }
        }
    }

}

