#include <iostream>
#include <string>
#include <list>

int main()
{
    std::list<std::string> lst;
    std::string word;
    auto iter = lst.begin();
    auto orig = iter;
    while (std::cin >> word) {
        iter = lst.insert(iter, word);
    }

    for (auto i:lst) {
        std::cout << i << " ";
    }
    if (lst.begin()==orig)
        std::cout << "\nlst.begin() & original iter is the same!!!\n";
    std::cout << std::endl;
    std::cout << *lst.begin() << " vs. " << *(--orig) << std::endl;
}
