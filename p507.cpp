#include <iostream>
#include <list>
#include <iterator>

int main()
{
    std::list<int> lst = {1, 2, 3, 4};
    std::list<int> lst2, lst3;

    copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
    for (auto i:lst2) std::cout << i << " ";
    std::cout << std::endl;
    copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
    for (auto i:lst3) std::cout << i << " ";
    std::cout << std::endl;
}
