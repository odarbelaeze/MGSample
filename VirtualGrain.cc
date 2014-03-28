#include "VirtualGrain.h"


VirtualGrain::VirtualGrain (const int& halfwidth, const int& nGrains = 1)
    :   _positions(nGrains)
{
    _width = 4 * halfwidth + 1;

    auto maxSize = 4 * halfwidth * halfwidth * halfwidth;

    _heads = std::vector<long> (nGrains, maxSize);

    for (auto&& grain : _positions)
    {
        std::vector<long> surface;

        while (grain.size() < maxSize)
        {
            if (grain.empty())
            {
                long c = (_width / 2) +
                         (_width / 2) * _width +
                         (_width / 2) * _width * _width;
                surface = _findNbs(c);
                grain.push_back(c);
            }
            else
            {
                long id = std::rand() % surface.size();
                long c = surface[id];
                
                grain.push_back(c);
                
                surface.erase(
                    std::remove(begin(surface), end(surface), c),
                    end(surface)
                );

                for (auto&& i : _findNbs(c))
                {
                    if (find(begin(grain), end(grain), i) == end(grain))
                    {
                        surface.push_back(i);
                    }
                }
            }
        }
    }
}


Vec3D VirtualGrain::pop(int gid = 0)
{
    long c = _positions.at(gid).at(-- _heads.at(gid));
    return Vec3D((c % _width) - _width / 2,
                 (c / _width) % _width - _width / 2,
                 (c / _width) / _width - _width / 2)
    ;
}


Vec3D VirtualGrain::top(int gid = 0) const
{
    long c = _positions.at(gid).at(_heads.at(gid) - 1);
    return Vec3D((c % _width) - _width / 2,
                 (c / _width) % _width - _width / 2,
                 (c / _width) / _width - _width / 2)
    ;
}


bool VirtualGrain::isEmpty(int gid = 0) const
{
    return _heads.at(gid) == 0;
}


double VirtualGrain::currentDist(int gid = 0) const
{
    return top(gid).norm();
}


bool VirtualGrain::available() const
{
    return std::any_of(begin(_heads), end(_heads), [](int head) { return head > 0; });
}


std::vector<long> VirtualGrain::_findNbs(long c)
{
    std::vector<long> nbs;
    nbs.push_back(c + 1);                   // North
    nbs.push_back(c - 1);                   // South
    nbs.push_back(c + _width);              // East
    nbs.push_back(c - _width);              // West
    nbs.push_back(c + _width * _width);     // Above
    nbs.push_back(c - _width * _width);     // Under
    return nbs;
}
