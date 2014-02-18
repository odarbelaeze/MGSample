#ifndef LINEAR_GRID_H_
#define LINEAR_GRID_H_

#include <cmath>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "Atom.h"

typedef Atom Point;
typedef Eigen::Vector3d Vec3D;

class LinearGrid
{
public:

    LinearGrid(const Vec3D&, const Vec3D&, const Vec3D&);
    LinearGrid(const Vec3D&, const Vec3D&, double);
    
    void insert(Point*);

    int  getCell(const Vec3D&) const;
    int  getCell(int, int, int) const;
    void findInBox(const Vec3D&, const Vec3D&, std::vector<Point*>&) const;
    void findInSphere(const Vec3D&, double, std::vector<Point*>&) const;

protected:

    Vec3D _origin;
    Vec3D _halfwidth;
    Vec3D _cell;
    std::vector<std::vector<Point*> > _data;

    int _w;
    int _l;
    int _h;

};

#endif