#include "Vec3D.h"
#include <valarray>


int main(int argc, char const *argv[])
{
    Vec3D a;
    Vec3D b;
    std::valarray<double> c;

    for (int i = 0; i < 10000000; ++i)
    {
        a = {1.0, 2.0, 3.0};
    }

    for (int i = 0; i < 10000000; ++i)
    {
        b = Vec3D(1.0, 2.0, 3.0);
    }

    for (int i = 0; i < 10000000; ++i)
    {
        c = {1.0, 2.0, 3.0};
    }

    return 0;
}
