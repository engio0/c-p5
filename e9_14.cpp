#include <iostream>
#include <string>
#include <list>
#include <vector>

int main()
{
    std::list<const char*> clist = {"ein", "zwei", "drei"};
    std::vector<std::string> vlist;
    vlist.assign(clist.cbegin(), clist.cend());
    for (auto i:vlist) {
        std::cout << i << " ";
    }
}
