#include "Sample.h"

#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char const *argv[])
{
    double width, lenght, height;
    double rad;

    po::options_description desc("Allowed options.");
    desc.add_options()
        ("help", "produce help message")
        (
            "width,w",
            po::value<double>(&width) -> default_value(20.0),
            "half width of the sample"
        )
        (
            "lenght,l",
            po::value<double>(&lenght) -> default_value(20.0),
            "half lenght of the sample"
        )
        (
            "height,h",
            po::value<double>(&height) -> default_value(10.0),
            "half height of the sample"
        )
        (
            "mean-rad,r",
            po::value<double>(&rad) -> default_value(10.0),
            "mean radius of the grains"
        )
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    Sample s(Vec3D(width, lenght, height), rad);

    std::cout << s << std::endl;

    return 0;
}
