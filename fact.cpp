#include <iostream>
#include <string>

#include "e6_9.h"

int fact(int val)
{
    int ret = 1;
    while (val > 1)
        ret *= val--;
    return ret;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage : fact num1 [numbers...]\n";
        return 1;
    }

    std::string sval;
    long long ival;
    for (int i = 1; i < argc; ++i) {
        sval = argv[i];
        try {
            ival = stoi(sval);
        }
        catch (const std::invalid_argument &ia) {
            std::cout << "ERROR !!! Invalid argument : "
                      << sval << " - " << ia.what() << std::endl;
            continue;
        }
        catch (const std::out_of_range &oor) {
            std::cout << "ERROR !!! Out of range : "
                      << sval << " - " << oor.what() << std::endl;
            continue;
        }
        std::cout << "fact(" << argv[i] << ") = " << fact(ival) << std::endl;
    }
}
