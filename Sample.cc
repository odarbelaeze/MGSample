#include "Sample.h"

Sample::Sample(Vec3D halfdim, double meanRad)
 : _halfdim(halfdim), _meanRad(meanRad), _octree(Vec3D(0.0, 0.0, 0.0), halfdim)
{
    int nSeeds = (6.0 * prod(_halfdim)) / (M_PI * std::pow(_meanRad, 3));

    for (int i = 0; i < nSeeds; ++i)
    {
        _seeds.push_back(Vec3D(
                0.5 - (double) std::rand() / RAND_MAX,
                0.5 - (double) std::rand() / RAND_MAX,
                0.5 - (double) std::rand() / RAND_MAX
            ) * 2.0 * _halfdim);
    }

    int width = std::pow(4.0 * prod(_halfdim), (1.0 / 3.0));
    width = std::max(width, 3 * (int) _meanRad);

    for (int i = 0; i < _seeds.size(); ++i)
    {
        _virtualGrains.push_back(VirtualGrain(_seeds[i], width));
    }

    _rads.resize(nSeeds);

    _addSpheres();
    while(_atomsAvailable())
    {
        _addNext();
    }
}


Sample::~Sample()
{}


std::ostream& operator<< (std::ostream& os, const Sample& s)
{
    for (int i = 0; i < s._atoms.size(); ++i)
    {
        os << s._atoms[i] -> pos[0] << " "
           << s._atoms[i] -> pos[1] << " "
           << s._atoms[i] -> pos[2] << " "
           << s._atoms[i] -> gid    << std::endl;
    }
    return os;
}


void Sample::_addSpheres()
{
    std::vector<bool> touched(_seeds.size(), false);

    while (std::any_of(begin(touched), end(touched), [](bool t){ return !t; }))
    {
        int i = std::rand() % _seeds.size();
        if (touched[i]) continue;

        for (int j = 0; j < _seeds.size(); ++j)
        {
            if (dist(_seeds[i], _seeds[j]) - (_rads[i] + _rads[j]) < 1.0 &&
                i != j)
            {
                touched[i] = true;
                touched[j] = true;
            }
        }

        if (!touched[i]) _rads[i] += 1.0;
    }

    for (int i = 0; i < _seeds.size(); ++i)
    {
        while(_virtualGrains[i].currentDist() < _rads[i])
        {
            Atom* atom = _virtualGrains[i].pop();
            _atoms.push_back(atom);
            _octree.insert(atom);
            std::cout << atom -> pos[0] << " "
                      << atom -> pos[1] << " "
                      << atom -> pos[2] << " "
                      << atom -> gid    << std::endl;
        }
    }
}


void Sample::_addNext()
{
    int i = std::rand() % _virtualGrains.size();

    while (_virtualGrains[i].isEmpty())
    {
        i = std::rand() % _virtualGrains.size();
    }

    Atom* atom = _virtualGrains[i].pop();
    std::vector<Atom*> atomsAround;

    _octree.getPointsInside(atom -> pos - 1.0, atom -> pos + 1.0, atomsAround);

    if (atomsAround.empty()) return;

    int nSame = std::count_if(begin(atomsAround), end(atomsAround), 
        [&, atom](const Atom* other) { return atom -> gid == other -> gid; });

    int nOther = atomsAround.size() - nSame;

    if (std::any_of(begin(atomsAround), end(atomsAround), 
        [&, atom](const Atom* other){ return dist(atom -> pos, other -> pos) < 0.5; }))
    {
        return;
    }

    if ( (nSame != 0) && (nSame > nOther) )
    {
        _atoms.push_back(atom);
        _octree.insert(atom);
        std::cout << atom -> pos[0] << " "
                  << atom -> pos[1] << " "
                  << atom -> pos[2] << " "
                  << atom -> gid    << std::endl;
    }

}


bool Sample::_atomsAvailable()
{
    return std::any_of(begin(_virtualGrains), end(_virtualGrains),
                       [](const VirtualGrain& vg) { return !vg.isEmpty();} );
}

