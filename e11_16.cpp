// Exercise 11.16: Using a map iterator write an expression that assigns a
// value to an element.

#include <map>
#include <iostream>
#include <string>

int main()
{
    std::map<int, std::string> numbers;
    int numint;
    std::string numstr;

    while (std::cin >> numint >> numstr) {
        auto it = numbers.find(numint);
        if (it == numbers.cend()) {
            numbers.insert(std::pair<int, std::string>(numint, numstr)); 
            std::cout << "New value added !!!\n";
        }
        else {
            std::cout << "Number " << numint << " changed from "
                      << it->second << " to " << (it->second = numstr) << std::endl;
        }
    }

    for (auto num:numbers) {
        std::cout << num.first << ", " << num.second << std::endl;
    }
}
