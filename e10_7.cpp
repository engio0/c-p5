// Exercise 10.7: Determine if there are any errors in the following programs
// and, if so, correct the error(s):
// (a)
// vector<int> vec; list<int> lst; int i;
// while (cin >> i)
// lst.push_back(i);
// copy(lst.cbegin(), lst.cend(), vec.begin());
// (b)
// vector<int> vec;
// vec.reserve(10); // reserve is covered in § 9.4 (p. 356)
// fill_n(vec.begin(), 10, 0);

#include <iostream>
#include <vector>
#include <list>

int main()
{
    std::vector<int> vec; std::list<int> lst; int i;
    while (std::cin >> i) {
        lst.push_back(i);
    }
    std::copy(lst.cbegin(), lst.cend(), back_inserter(vec));
    for (auto x:vec) std::cout << x << " ";
    std::cout << std::endl;
    for (auto x:lst) std::cout << x << " ";
    std::cout << std::endl;


    vec.reserve(10);
    std::fill_n(vec.begin(), 10, 0);
    for (auto x:vec) std::cout << x << " ";
    std::cout << std::endl;
    std::fill_n(std::back_inserter(vec), 10, 0);
    for (auto x:vec) std::cout << x << " ";
}
