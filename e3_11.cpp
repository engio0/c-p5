#include <iostream>
#include <string>

int main()
{
    const std::string s = "Keep Out!";
    for (auto &c:s) std::cout << c << ":";
}
