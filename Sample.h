#ifndef SAMPLE_H_
#define SAMPLE_H_

#include "Atom.h"
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
    Sample(Vec3D, double);
    ~Sample();

    friend std::ostream& operator<< (std::ostream&, const Sample&);

private:

    void _addSpheres();
    void _addNext();
    bool _atomsAvailable();

    Vec3D _halfdim;
    double _meanRad;

    std::vector<Vec3D> _seeds;
    std::vector<double> _rads;
    std::vector<VirtualGrain> _virtualGrains;
    std::vector<Atom*> _atoms;

    Octree _octree;

};

#endif
