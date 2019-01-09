// Exercise 10.27: In addition to unique (§ 10.2.3, p. 384), the library
// defines function named unique_copy that takes a third iterator denoting a
// destination into which to copy the unique elements. Write a program that
// uses unique_copy to copy the unique elements from a vector into an
// initially empty list.

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> input;
    std::list<std::string> output;
    std::string buffer;

    while (std::cin >> buffer) {
        input.push_back(buffer);
    }

//    for (auto i:input) {
//        std::cout << i << std::endl;
//    }
//
//    std::cout << "=================================================\n";

    sort(input.begin(), input.end());

    unique_copy(input.cbegin(), input.cend(), back_inserter(output));

    for (auto i:output) {
        std::cout << i << std::endl;
    }
}
