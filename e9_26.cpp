// #Exercise 9.26: Using the following definition of ia, copy ia into a vector
// and into a list. Use the single-iterator form of erase to remove the
// elements with odd values from your list and the even values from your
// vector.include <iostream>

#include <iostream>
#include <vector>
#include <list>

int main()
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55,89};
    std::vector<int> ivec(ia, std::end(ia));
    std::list<int> ilist(ivec.begin(), ivec.end());

    for (auto i:ilist) std::cout << i << " ";
    std::cout << std::endl;
    for (auto i:ivec) std::cout << i << " ";
    std::cout << std::endl;

    for (auto i = ilist.cbegin(); i != ilist.cend(); ++i) {
        if (*i % 2) {
            std::cout << *i << " is odd number, will be deleted\n";
            ilist.erase(i);
        }
    }
    for (auto i = ivec.cbegin(); i != ivec.cend(); ++i) {
        if (!(*i % 2)) {
            std::cout << *i << " is even number, will be deleted\n";
            ivec.erase(i);
        }
    }

    for (auto i:ilist) std::cout << i << " ";
    std::cout << std::endl;
    for (auto i:ivec) std::cout << i << " ";
    std::cout << std::endl;
}
