#include <vector>
#include <list>
#include <iostream>

int main()
{
    std::list<int> li = {0, 1, 2, 3, 4};
    std::vector<int> vi = {6, 7, 8, 9, 10};

    std::vector<double> v1(li.cbegin(), li.cend());
    std::vector<double> v2(vi.cbegin(), vi.cend());

    for (auto x:v1) std::cout << x << " ";
    std::cout << std::endl;

    for (auto x:v2) std::cout << x << " ";
    std::cout << std::endl;
}
