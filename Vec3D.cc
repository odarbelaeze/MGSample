#include "Vec3D.h"

Vec3D::Vec3D()
 : _x{0.0}, _y{0.0}, _z{0.0}
{
}


Vec3D::Vec3D(double x, double y, double z)
 : _x{x}, _y{y}, _z{z}
{
}


Vec3D::Vec3D(std::initializer_list<double> il)
{
    if (il.size() != 3) throw ShapeException();
    auto ilf = begin(il);
    _x = *(ilf + 0);
    _y = *(ilf + 1);
    _z = *(ilf + 2);
}


double Vec3D::x() const
{
    return _x;
}


double Vec3D::y() const
{
    return _y;
}


double Vec3D::z() const
{
    return _z;
}


const double& Vec3D::operator[] (int i) const
{
    switch (i)
    {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            throw OutOfBounds();
            break;
    }
}


double& Vec3D::operator[] (int i)
{
    switch (i)
    {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            throw OutOfBounds();
            break;
    }
}


Vec3D& Vec3D::operator= (std::initializer_list<double> il)
{
    if (il.size() != 3) throw ShapeException();
    auto ilf = begin(il);
    _x = *(ilf + 0);
    _y = *(ilf + 1);
    _z = *(ilf + 2);
}


Vec3D Vec3D::operator+ ()
{
    return *this;
}


Vec3D Vec3D::operator- ()
{
    return Vec3D(- _x, - _y, - _z);
}


Vec3D Vec3D::operator+= (const Vec3D& other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}


Vec3D Vec3D::operator-= (const Vec3D& other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}


Vec3D Vec3D::operator*= (const Vec3D& other)
{
    _x *= other._x;
    _y *= other._y;
    _z *= other._z;
    return *this;
}


Vec3D Vec3D::operator/= (const Vec3D& other)
{
    _x /= other._x;
    _y /= other._y;
    _z /= other._z;
    return *this;
}


Vec3D Vec3D::operator+= (const double& c)
{
    _x += c;
    _y += c;
    _z += c;
    return *this;
}


Vec3D Vec3D::operator-= (const double& c)
{
    _x -= c;
    _y -= c;
    _z -= c;
    return *this;
}


Vec3D Vec3D::operator*= (const double& c)
{
    _x *= c;
    _y *= c;
    _z *= c;
    return *this;
}


Vec3D Vec3D::operator/= (const double& c)
{
    _x /= c;
    _y /= c;
    _z /= c;
    return *this;
}

Vec3D operator+ (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    ans[0] = a[0] + b[0];
    ans[1] = a[1] + b[1];
    ans[2] = a[2] + b[2];
    return ans;
}


Vec3D operator- (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    ans[0] = a[0] - b[0];
    ans[1] = a[1] - b[1];
    ans[2] = a[2] - b[2];
    return ans;
}


Vec3D operator* (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    ans[0] = a[0] * b[0];
    ans[1] = a[1] * b[1];
    ans[2] = a[2] * b[2];
    return ans;
}


Vec3D operator/ (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    ans[0] = a[0] / b[0];
    ans[1] = a[1] / b[1];
    ans[2] = a[2] / b[2];
    return ans;
}


Vec3D operator+ (const Vec3D& v, const double& c)
{
    Vec3D ans;
    ans[0] = v[0] + c;
    ans[1] = v[1] + c;
    ans[2] = v[2] + c;
    return ans;
}


Vec3D operator- (const Vec3D& v, const double& c)
{
    Vec3D ans;
    ans[0] = v[0] - c;
    ans[1] = v[1] - c;
    ans[2] = v[2] - c;
    return ans;
}


Vec3D operator* (const Vec3D& v, const double& c)
{
    Vec3D ans;
    ans[0] = v[0] * c;
    ans[1] = v[1] * c;
    ans[2] = v[2] * c;
    return ans;
}


Vec3D operator/ (const Vec3D& v, const double& c)
{
    Vec3D ans;
    ans[0] = v[0] / c;
    ans[1] = v[1] / c;
    ans[2] = v[2] / c;
    return ans;
}


Vec3D operator+ (const double& c, const Vec3D& v)
{
    Vec3D ans;
    ans[0] =  c + v[0];
    ans[1] =  c + v[1];
    ans[2] =  c + v[2];
    return ans;
}


Vec3D operator- (const double& c, const Vec3D& v)
{
    Vec3D ans;
    ans[0] =  c - v[0];
    ans[1] =  c - v[1];
    ans[2] =  c - v[2];
    return ans;
}


Vec3D operator* (const double& c, const Vec3D& v)
{
    Vec3D ans;
    ans[0] =  c * v[0];
    ans[1] =  c * v[1];
    ans[2] =  c * v[2];
    return ans;
}


Vec3D operator/ (const double& c, const Vec3D& v)
{
    Vec3D ans;
    ans[0] =  c / v[0];
    ans[1] =  c / v[1];
    ans[2] =  c / v[2];
    return ans;
}


Vec3D abs (const Vec3D& v)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = std::abs(v[i]);
    }
    return ans;
}


Vec3D min (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = a[i] < b[i] ? a[i] : b[i];
    }
    return ans;
}


Vec3D cross (const Vec3D& u, const Vec3D& v)
{
    Vec3D ans;
    ans[0] = u[1] * v[2] - u[2] * v[1];
    ans[1] = u[2] * v[0] - u[0] * v[2];
    ans[2] = u[0] * v[1] - u[1] * v[0];
    return ans;
}


double min (const Vec3D& v)
{
    return std::min(v[0], std::min(v[1], v[2]));
}


double sum (const Vec3D& v)
{
    return v[0] + v[1] + v[2];
}


double prod (const Vec3D& v)
{
    return v[0] * v[1] * v[2];
}


double norm (const Vec3D& v)
{
    return std::sqrt(dot(v, v));
}


double dot (const Vec3D& a, const Vec3D& b)
{
    return sum(a * b);
}


double dist (const Vec3D& a, const Vec3D& b)
{
    return norm(b - a);
}


Vec3D randomUnit()
{
    double theta = 1.0 * M_PI * std::rand() / RAND_MAX;
    double phi   = 2.0 * M_PI * std::rand() / RAND_MAX;
    return Vec3D(
        std::sin(theta) * std::sin(phi),
        std::sin(theta) * std::cos(phi),
        std::cos(theta)
        );
}


std::ostream& operator<< (std::ostream& os, const Vec3D& v)
{
    return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}
