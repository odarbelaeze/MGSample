#include "Vec3D.h"

Vec3D::Vec3D()
{
    _data = new double[3];
}


Vec3D::Vec3D(const Vec3D& other)
 : _data(new double[3])
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] = other._data[i];
    }
}


Vec3D::Vec3D(Vec3D&& other)
 : _data(other._data)
{
    other._data = nullptr;
}


Vec3D::Vec3D(double x, double y, double z)
 : _data(new double[3])
{
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}


Vec3D::Vec3D(std::initializer_list<double> il)
{
    if (il.size() != 3) throw ShapeException();
    if (_data == nullptr) _data = new double[3];
    auto ilf = begin(il);
    _data[0] = *(ilf + 0);
    _data[1] = *(ilf + 1);
    _data[2] = *(ilf + 2);
}


Vec3D::~Vec3D()
{
    _data = nullptr;
}


double Vec3D::x() const
{
    return _data[0];
}


double Vec3D::y() const
{
    return _data[1];
}


double Vec3D::z() const
{
    return _data[2];
}


double& Vec3D::operator[] (int i) const
{
    if (i < 0 || i > 2) throw OutOfBounds();
    return _data[i];
}


Vec3D& Vec3D::operator= (const Vec3D& other)
{
    if (this != &other)
    {
        if (_data == nullptr) _data = new double[3];
        for (int i = 0; i < 3; ++i)
        {
            _data[i] = other._data[i];
        }
    }
    return *this;
}


Vec3D& Vec3D::operator= (Vec3D&& other)
{
    if (this != &other)
    {
        if (_data != nullptr) delete _data;
        _data = other._data;
        other._data = nullptr;
    }
    return *this;
}


Vec3D& Vec3D::operator= (std::initializer_list<double> il)
{
    if (il.size() != 3) throw ShapeException();
    if (_data == nullptr) _data = new double[3];
    auto ilf = begin(il);
    _data[0] = *(ilf + 0);
    _data[1] = *(ilf + 1);
    _data[2] = *(ilf + 2);
}


Vec3D Vec3D::operator+ ()
{
    return *this;
}


Vec3D Vec3D::operator- ()
{
    return Vec3D(- _data[0], - _data[1], - _data[2]);
}


Vec3D Vec3D::operator+= (const Vec3D& other)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] += other._data[i];
    }
    return *this;
}


Vec3D Vec3D::operator-= (const Vec3D& other)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] -= other._data[i];
    }
    return *this;
}


Vec3D Vec3D::operator*= (const Vec3D& other)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] *= other._data[i];
    }
    return *this;
}


Vec3D Vec3D::operator/= (const Vec3D& other)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] /= other._data[i];
    }
    return *this;
}


Vec3D Vec3D::operator+= (const double& c)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] += c;
    }
    return *this;
}


Vec3D Vec3D::operator-= (const double& c)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] -= c;
    }
    return *this;
}


Vec3D Vec3D::operator*= (const double& c)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] *= c;
    }
    return *this;
}


Vec3D Vec3D::operator/= (const double& c)
{
    for (int i = 0; i < 3; ++i)
    {
        _data[i] /= c;
    }
    return *this;
}

Vec3D operator+ (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = a[i] + b[i];
    }
    return ans;
}


Vec3D operator- (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = a[i] - b[i];
    }
    return ans;
}


Vec3D operator* (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = a[i] * b[i];
    }
    return ans;
}


Vec3D operator/ (const Vec3D& a, const Vec3D& b)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = a[i] / b[i];
    }
    return ans;
}


Vec3D operator+ (const Vec3D& v, const double& c)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = v[i] + c;
    }
    return ans;
}


Vec3D operator- (const Vec3D& v, const double& c)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = v[i] - c;
    }
    return ans;
}


Vec3D operator* (const Vec3D& v, const double& c)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = v[i] * c;
    }
    return ans;
}


Vec3D operator/ (const Vec3D& v, const double& c)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = v[i] / c;
    }
    return ans;
}


Vec3D operator+ (const double& c, const Vec3D& v)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = c + v[i];
    }
    return ans;
}


Vec3D operator- (const double& c, const Vec3D& v)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = c - v[i];
    }
    return ans;
}


Vec3D operator* (const double& c, const Vec3D& v)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = c * v[i];
    }
    return ans;
}


Vec3D operator/ (const double& c, const Vec3D& v)
{
    Vec3D ans;
    for (int i = 0; i < 3; ++i)
    {
        ans[i] = c / v[i];
    }
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


double sum (const Vec3D& v)
{
    return v[0] + v[1] + v[2];
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


std::ostream& operator<< (std::ostream& os, const Vec3D& v)
{
    return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}
