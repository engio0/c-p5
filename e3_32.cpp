// Exercise 3.32: Copy the array you defined in the previous exercise into
// another array. Rewrite your program to use vectors.

#include <iostream>
#include <cstddef>
#include <vector>

int main()
{
    constexpr size_t arrsz = 10;

    int intarr[arrsz];
    std::vector<int> intvec;

    for (auto i = 0; i < arrsz; ++i) {
        intarr[i] = i;
    }

    std::cout << "array contains...\n";
    for (auto i:intarr) {
        std::cout << i << std::endl;
    }

    for (auto i:intarr) {
        intvec.push_back(i);
    }

    std::cout << "vector contains...\n";
    for (auto i:intvec) {
        std::cout << i << std::endl;
    }
}
