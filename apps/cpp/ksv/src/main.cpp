#include <iostream>
#include <string>
#include <vector>

#include "KSV.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "No valid configuration file sent" << std::endl;
        exit(1);
    }

    const std::string &cfg(argv[2]);
    KSV ksv(cfg);

    ksv.run();

    return 0;
}