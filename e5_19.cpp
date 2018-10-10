#include <iostream>
#include <string>

int main()
{
    std::string str1, str2;

    do {
        std::cin >> str1 >> str2;
        std::cout << str1 << (str1 == str2 ? " = " : (str1 > str2 ? " > " : " < ")) << str2 << '\n';
    } while (str1 != "quit" || str2 != "quit");
}
