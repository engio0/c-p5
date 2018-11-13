#include <iostream>

int main()
{
    std::cout << "&std::cout : " << &std::cout << std::endl;
    std::cin.tie(&std::cout);
    std::ostream *old_tie = std::cin.tie(nullptr);
    std::cin.tie(&std::cerr);
    std::cout << "&std::cerr : " << &std::cerr << std::endl;
    std::cin.tie(old_tie);
}
