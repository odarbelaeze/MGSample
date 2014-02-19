#ifndef SEED_H_
#define SEED_H_

#include <cmath>
#include <random>

#include <eigen3/Eigen/Dense>

typedef Eigen::Quaternion<double> Quaternion;
typedef Eigen::AngleAxis<double> AngleAxis;

typedef Eigen::Vector3d Vec3D;

struct Seed
{
    Vec3D origin;
    Quaternion rotation;
    unsigned int id;

    Seed(Vec3D);
    Seed(Vec3D, Quaternion);

    Vec3D getRealPos(Vec3D);

    static std::mt19937_64 generator;
    static std::uniform_real_distribution<double> dist;

    protected: static unsigned int currId;
};

#endif