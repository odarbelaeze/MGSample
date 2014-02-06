#ifndef VEC3D_H_
#define VEC3D_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

class ShapeException : public std::exception {};
class OutOfBounds : public std::exception {};

class Vec3D
{
public:
    Vec3D();
    Vec3D(const Vec3D&);
    Vec3D(Vec3D&&);
    Vec3D(double, double, double);
    Vec3D(std::initializer_list<double>);
    ~Vec3D();

    double x() const;
    double y() const;
    double z() const;

    double& operator[] (int) const;

    Vec3D& operator= (const Vec3D&);
    Vec3D& operator= (Vec3D&&);
    Vec3D& operator= (std::initializer_list<double>);

    Vec3D operator+ ();
    Vec3D operator- ();

    Vec3D operator+= (const Vec3D&);
    Vec3D operator-= (const Vec3D&);
    Vec3D operator*= (const Vec3D&);
    Vec3D operator/= (const Vec3D&);

    Vec3D operator+= (const double&);
    Vec3D operator-= (const double&);
    Vec3D operator*= (const double&);
    Vec3D operator/= (const double&);

private:
    double* _data;

};

Vec3D operator+ (const Vec3D&, const Vec3D&);
Vec3D operator- (const Vec3D&, const Vec3D&);
Vec3D operator* (const Vec3D&, const Vec3D&);
Vec3D operator/ (const Vec3D&, const Vec3D&);

Vec3D operator+ (const Vec3D&, const double&);
Vec3D operator- (const Vec3D&, const double&);
Vec3D operator* (const Vec3D&, const double&);
Vec3D operator/ (const Vec3D&, const double&);

Vec3D operator+ (const double&, const Vec3D&);
Vec3D operator- (const double&, const Vec3D&);
Vec3D operator* (const double&, const Vec3D&);
Vec3D operator/ (const double&, const Vec3D&);

Vec3D abs (const Vec3D&);
Vec3D min (const Vec3D&, const Vec3D&);
Vec3D cross (const Vec3D&, const Vec3D&);

double min (const Vec3D&);
double sum (const Vec3D&);
double prod (const Vec3D&);
double norm (const Vec3D&);
double dot (const Vec3D&, const Vec3D&);
double dist (const Vec3D&, const Vec3D&);

Vec3D randomUnit();

std::ostream& operator<< (std::ostream&, const Vec3D&);

#endif