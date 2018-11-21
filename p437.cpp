#include <iostream>
#include <list>

int main()
{
    std::list<int> ilist;
    for (size_t ix = 0; ix != 4; ++ix)
        ilist.push_front(ix);

    for (auto iv:ilist)
        std::cout << iv << " ";
}
