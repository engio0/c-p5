#include <iostream>

int main()
{
    int i = 0;
    std::cout << "i = " << i << std::endl;

    ++++i;
    std::cout << i << std::endl;
    (i++)++;
    std::cout << i << std::endl;
}
