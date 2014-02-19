#include "Sample.h"

Sample::Sample(const Vec3D& halfdim, double meanRad)
    :   _halfdim(halfdim),
        _meanRad(meanRad),
        _virtualGrain(0, 1),
        _linearGrid(Vec3D::Zero(), halfdim, 1.0)
{
    _nSeeds = (6.0 * _halfdim.prod()) / (M_PI * std::pow(_meanRad, 3));

    for (int i = 0; i < _nSeeds; ++i)
    {
        _seeds.push_back(
            Seed(Vec3D::Random().array() * (_halfdim.array() - 0.5 * meanRad))
        );
    }

    int width = std::min(0.5 * _halfdim.maxCoeff(), 3 * meanRad);

    _virtualGrain = VirtualGrain(width, _nSeeds);

    _rads.resize(_nSeeds);

    _addSpheres();
    
    while(_virtualGrain.available())
    {
        _addNext();
    }
}


std::ostream& operator<< (std::ostream& os, const Sample& s)
{
    for (int i = 0; i < s._atoms.size(); ++i)
    {
        os << s._atoms[i] -> pos(0) << " "
           << s._atoms[i] -> pos(1) << " "
           << s._atoms[i] -> pos(2) << " "
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
            if (((_seeds[j].origin, _seeds[j].origin).norm() - 
                 (_rads[i] + _rads[j]) < 1.0                   )

                && i != j)
            {
                touched[i] = true;
                touched[j] = true;
            }
        }

        if (!touched[i]) _rads[i] += 1.0;
    }

    for (int i = 0; i < _seeds.size(); ++i)
    {
        while(_virtualGrain.currentDist(i) < _rads[i])
        {
            Atom* atom = new Atom(
                _seeds[i].getRealPos(_virtualGrain.pop(i)),
                _seeds[i].id 
            );

            if (((atom -> pos).array() < _halfdim.array()).minCoeff() &&
                ((atom -> pos).array() > (- _halfdim.array())).minCoeff())
            {
                _atoms.push_back(atom);
                _linearGrid.insert(atom);
            }

        }
    }
}


void Sample::_addNext()
{
    int i = std::rand() % _seeds.size();

    while (_virtualGrain.isEmpty(i))
    {
        i = std::rand() % _seeds.size();
    }

    Atom* atom = new Atom(
        _seeds[i].getRealPos(_virtualGrain.pop(i)),
        _seeds[i].id 
    );

    std::vector<Atom*> atomsAround;

    _linearGrid.findInSphere(atom -> pos, 1.1, atomsAround);

    if (atomsAround.empty()) return;

    int nSame = std::count_if(begin(atomsAround), end(atomsAround), 
        [&, atom](const Atom* other) { 
            return atom -> gid == other -> gid;
        });

    int nOther = atomsAround.size() - nSame;

    if (std::any_of(begin(atomsAround), end(atomsAround), 
        [&, atom](const Atom* other){ 
            return (other -> pos - atom -> pos).norm() < 0.5; }))
    {
        return;
    }

    if ( (nSame != 0) && (nSame > nOther) )
    {
        if (((atom -> pos).array() < _halfdim.array()).minCoeff() &&
            ((atom -> pos).array() > (- _halfdim.array())).minCoeff())
        {
            _atoms.push_back(atom);
            _linearGrid.insert(atom);
        }
    }

}

