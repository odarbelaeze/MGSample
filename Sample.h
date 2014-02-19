#ifndef SAMPLE_H_
#define SAMPLE_H_

#include "Atom.h"
#include "Seed.h"
#include "LinearGrid.h"
#include "VirtualGrain.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <eigen3/Eigen/Dense>

typedef Eigen::Vector3d Vec3D;

class Sample
{
public:
    Sample(const Vec3D&, double);

    friend std::ostream& operator<< (std::ostream&, const Sample&);

private:

    void _addSpheres();
    void _addNext();

    Vec3D  _halfdim;
    double _meanRad;
    int    _nSeeds;

    VirtualGrain _virtualGrain;
    
    std::vector<Seed> _seeds;
    std::vector<double> _rads;
    std::vector<Atom*> _atoms;

    LinearGrid _linearGrid;

};

#endif
