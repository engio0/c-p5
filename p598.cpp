#include <iostream>

int main()
{
    char arr[0];
    char *cp = new char[0];

    std::cout << (void*)cp << std::endl;
    cp = new char[5]{'H', 'e', 'l', 'l', 'o'};
    std::cout << (void*)cp << std::endl;
}
