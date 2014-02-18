#include "Sample.h"
#include <valarray>


int main(int argc, char const *argv[])
{
    Sample s({10, 10, 50}, 10.0);
    std::cout << s << std::endl;

    return 0;
}
