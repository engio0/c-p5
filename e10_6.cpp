// Exercise 10.6: Using fill_n, write a program to set a sequence of int
// values to 0.include <algorithm>

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> ivec(8, 10);
    std::fill_n(ivec.begin(), 6, 6);

    for (auto x:ivec) {
        std::cout << x << ", ";
    }
}
