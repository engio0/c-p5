#include <iostream>

int main()
{
    std::cout << int('2') << ' ' << int('M') << std::endl;
    std::cout << "\x32\x4d\n" << std::endl;
    std::cout << "\x32\t\x4d\n" << std::endl;

    return 0;
}
