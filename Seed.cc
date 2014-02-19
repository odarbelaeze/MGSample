#include "Seed.h"

std::mt19937_64 Seed::generator;
std::uniform_real_distribution<double> Seed::dist(0, M_PI);

unsigned int Seed::currId = 0;

Seed::Seed(Vec3D _origin)
    :   origin(_origin),
        id(currId ++)
{
    rotation = AngleAxis(dist(generator), Vec3D::Random().normalized());
}


Seed::Seed(Vec3D _origin, Quaternion _rotation)
    :   origin(_origin),
        rotation(_rotation),
        id(currId ++)
{

}


Vec3D Seed::getRealPos(Vec3D _intPos)
{
    return (rotation * _intPos) + origin;
}
