/*
 * Exercise 3.15: Repeat the previous program but read strings this time.
 */

#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string word;
    std::vector<std::string> table;

    std::cout << "Enter words : \n";

    while (std::cin >> word)
        table.push_back(word);

    std::cout << "The number of words : " << table.size() << std::endl;

    for (auto a : table)
        std::cout << a << ", ";
}
