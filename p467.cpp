#include <iostream>
#include <string>

int main()
{
    std::string s2 = "pi = 3.14159. Did you know that?\n";
    auto d = std::stod(s2.substr(s2.find_first_of("+-.0123456789")));
    std::cout << d << std::endl;
}
