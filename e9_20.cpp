#include <iostream>
#include <list>
#include <deque>

int main()
{
    std::list<int> ilist;
    std::deque<int> odd, even;

    int tmp;
    while (std::cin >> tmp) {
        ilist.push_back(tmp);
    }

    for (auto it = ilist.begin(); it != ilist.end(); ++it) { // for (auto i : ilist)
        if (*it % 2)                                         //     (i & 0x1 ? ood : even).push_back(i);
            odd.push_back(*it);
        else
            even.push_back(*it);
    }

    for (auto x:odd) std::cout << x << " ";
    std::cout << std::endl;
    for (auto x:even) std::cout << x << " ";
}
