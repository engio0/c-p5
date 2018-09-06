#include <iostream>

int main()
{
    int i = 0, &r1 = i;
    double d = 0, &r2 = d;

    std::cout << "i = " << i << ", r1 = " << r1 << std::endl;
    std::cout << "d = " << d << ", r2 = " << r2 << std::endl;

    r2 = 3.14159;
    std::cout << "r2 = 3.14159, r2 = " << r2 << std::endl;

    r2 = r1;
    std::cout << "r2 = r1, r2 = " << r2 << std::endl;

    i = r2;
    std::cout << "i = r2, i = " << i << std::endl;

    r1 = d;
    std::cout << "r1 = d, r1 = " << r1 << std::endl;
}
