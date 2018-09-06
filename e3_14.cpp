/*
 * Exercise 3.14: Write a program to read a sequence of ints from cin and
 * store those values in a vector.
 */

#include <iostream>
#include <vector>

int main()
{
    int val;
    std::vector<int> table;

    while (std::cin >> val)
        table.push_back(val);

    for (int a : table)
        std::cout << a << " ";
}
