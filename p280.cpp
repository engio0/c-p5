#include <iostream>
#include <string>

std::string::size_type find_char(const std::string &s, const char &c,
                            std::string::size_type &occurs)
{
    auto ret = s.size();
    occurs = 0;
    for (decltype(ret) i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}

int main()
{
    std::string buffer;
    std::string::size_type rep;
    std::string::size_type pos;
    char c;

    std::cout << "Enter a string : \n";
    std::getline(std::cin, buffer);
    std::cout << "Enter a character (. to quit) : \n";
    while (std::cin >> c) {
        if (c == '.') break;
        pos = find_char(buffer, c, rep);   
        std::cout << "The character \"" << c << "\" occurred "
                  << rep << " time(s)\n";
        if (rep) std::cout << "\tat pos " << pos << ".\n";
    }
}
