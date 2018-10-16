#include <iostream>
#include <string>

bool has_capital(const std::string &str)
{
    for (auto c : str) {
        if (c >= 'A' && c <= 'Z')
            return true;
    }
    return false;
}

void to_lower(std::string &str)
{
    for (auto &c : str) {
        if (c >= 'A' && c <= 'Z')
            c -= 'A' - 'a';
    }
}

int main()
{
    std::cout << "Enter a string :\n";
    std::string buffer;
    std::getline(std::cin, buffer);
    std::cout << "The string has " << ( has_capital(buffer) ? "a" : "no" ) << " capital letter.\n";
    std::cout << "Converted to all lowers :\n";
    to_lower(buffer);
    std::cout << buffer;
}
