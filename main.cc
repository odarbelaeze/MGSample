#include <iostream>

#include "VirtualGrain.h"

int main(int argc, char const *argv[])
{
    VirtualGrain vg(50, 10);

    while (!vg.isEmpty(0))
    {
        std::cout << vg.pop(0).norm() << std::endl;
    }

    return 0;
}
