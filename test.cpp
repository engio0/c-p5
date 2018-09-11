#include <iostream>

int main()
{
    bool b = 42;
    std::cout << "bool b = 42, b = " << b << std::endl;

    int i = b;
    std::cout << "int i = b, i = " << i << std::endl;

    i = 3.14;
    std::cout << "i = 3.14, i = " << i << std::endl;

    double pi = i;
    std::cout << "double pi = i, pi = " << pi << std::endl;

    unsigned char c = -1;
    std::cout << "unsigned char c = -1, c = " << c << std::endl;

    int uc2i = c;
    std::cout << "int uc2i = c, uc2i = " << uc2i << std::endl;

    signed char c2 = 256;
    std::cout << "signed char c2 = 256, c2 = " << c2 << std::endl;

    int c2i = c2;
    std::cout << "int c2i = c2, c2i = " << c2i << std::endl;

    unsigned u = 10;
    i = -42;
    std::cout << "(-42) + (-42) = " << i + i << std::endl;
    std::cout << u + i << std::endl;

    i = -1;
    u = 1;
    std::cout << "int(-1) * unsigned(1) = " << i*u << std::endl;

    std::cout << "unsigned(-1) = " << unsigned(-1) << std::endl;

    return 0;
}
