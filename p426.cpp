#include <iostream>
#include <string>
#include <list>

int main()
{
    std::list<std::string> a = {"Milton", "Shakespeare", "Austen"};

    auto it1 = a.begin();
    auto it1r = a.end();
    auto it2 = a.rbegin();
    auto it2r = a.rend();
    
    std::cout << *it1 << std::endl;
    std::cout << *it2 << std::endl;
}
