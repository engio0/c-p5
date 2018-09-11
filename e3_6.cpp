#include <iostream>
#include <string>

int main()
{
    std::string str("some string");

    std::cout << str << std::endl;
    for (auto &c : str)
        c = 'X';

    std::cout << str << std::endl;
}
