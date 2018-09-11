// Exercise 3.31: Write a program to define an array of ten ints. Give each
// element the same value as its position in the array.

#include <iostream>
#include <cstddef>

int main()
{
    constexpr size_t arrsz = 10;

    int intarr[arrsz];

    for (auto i = 0; i < arrsz; ++i) {
        intarr[i] = i;
    }

    for (auto i:intarr) {
        std::cout << i << std::endl;
    }
}
