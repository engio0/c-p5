#include <iostream>

int main()
{
    int someValue = 666;
    int x = 0, y = 0;

    someValue ? ++x, ++y : --x, --y;

    std::cout << someValue << ", " << x << ", " << y << std::endl;
}
