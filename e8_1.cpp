#include <iostream>
#include <string>

std::istream& func(std::istream& is)
{
    std::string buf;
    while (std::cin >> buf) {
        std::cout << buf << std::endl;
    }
    is.clear();
    return is;
}

int main()
{
    std::istream& is = func(std::cin);
    std::cout << is.rdstate() << std::endl;
}
