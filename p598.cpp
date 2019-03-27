#include <iostream>

int main()
{
    char arr[0];
    std::cout << (void*)arr << std::endl;

    char *cp = new char[0];

    std::cout << (void*)cp << std::endl;
    cp = new char[5]{'H', 'e', 'l', 'l', 'o'};
    std::cout << (void*)cp << std::endl;

    std::cout << cp[0] << ", " << cp[1] << std::endl;

    delete[] cp;
    std::cout << cp[0] << ", " << cp[1] << std::endl;
}
