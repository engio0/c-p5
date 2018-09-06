#include <iostream>
#include <string>

int main()
{
    std::string str("some string");

    if (std::cin >> str) {
        std::cout << str << std::endl;
        for (char &c : str)
            c = 'X';

        std::cout << str << std::endl;
    }
}
