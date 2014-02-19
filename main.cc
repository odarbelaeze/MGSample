#include <iostream>

#include "Sample.h"

int main(int argc, char const *argv[])
{
    Sample s(Vec3D(20.0, 20.0, 5.0), 2.5);

    std::cout << s << std::endl;

    return 0;
}
