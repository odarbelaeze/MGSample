#include "VirtualGrain.h"


VirtualGrain::VirtualGrain (const int& halfwidth, const int& ngrains = 1)
    :   _positions(std::pow(2 * halfwidth + 1, 3)),
        _heads(ngrains, std::pow(2 * halfwidth + 1, 3))
{
    std::vector<Vec3D> basis({ Vec3D(0.0, 0.0, 0.0) });

    int id = 0;

    for (int i = - halfwidth; i <= halfwidth; ++i)
    {
        for (int j = - halfwidth; j <= halfwidth; ++j)
        {
            for (int k = - halfwidth; k <= halfwidth; ++k)
            {
                for (auto&& pos : basis)
                {
                    _positions.at(id ++) = Vec3D(i, j, k) + pos;
                }
            }
        }
    }

    std::sort(begin(_positions), end(_positions), 
        [&, this](const Vec3D& a, const Vec3D& b) {
            return a.norm() > b.norm();
        }
    );
}


VirtualGrain::VirtualGrain (
    const std::vector<Vec3D>& basis,
    const int& halfwidth,
    const int& ngrains = 1
)
    :   _positions(std::pow(2 * halfwidth, 3) * basis.size()),
        _heads(ngrains, std::pow(2 * halfwidth, 3) * basis.size())
{
    int id = 0;

    for (int i = - halfwidth; i <= halfwidth; ++i)
    {
        for (int j = - halfwidth; j <= halfwidth; ++j)
        {
            for (int k = - halfwidth; k <= halfwidth; ++k)
            {
                for (auto&& pos : basis)
                {
                    _positions.at(id ++) = Vec3D(i, j, k) + pos;
                }
            }
        }
    }

    std::sort(begin(_positions), end(_positions), 
        [&, this](const Vec3D& a, const Vec3D& b) {
            return a.norm() > b.norm();
        }
    );
}


Vec3D VirtualGrain::pop(int gid = 0)
{
    return _positions.at(-- _heads.at(gid));
}


Vec3D VirtualGrain::top(int gid = 0) const
{
    return _positions.at(_heads.at(gid) - 1);
}


bool VirtualGrain::isEmpty(int gid = 0) const
{
    return _heads.at(gid) == 0;
}


double VirtualGrain::currentDist(int gid = 0) const
{
    return _positions.at(_heads.at(gid) - 1).norm();
}


bool VirtualGrain::available() const
{
    return std::any_of(begin(_heads), end(_heads), [](int head) { return head > 0; });
}

