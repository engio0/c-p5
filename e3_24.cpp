// Exercise 3.24: Redo the last exercise from ¡× 3.3.3 (p. 105, E3.20) using iterators.
// Exercise 3.20: Read a set of integers into a vector. Print the sum of each
// pair of adjacent elements. Change your program so that it prints the sum of
// the first and last elements, followed by the sum of the second and second-to-last,
// and so on.

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers;
    int val;

    std::cout << "Enter integers...\n";

    while (std::cin >> val) {
        numbers.push_back(val);
    }
    
    std::cout << "Printing the sum of adjacent pairs...\n";
    for (auto i = numbers.cbegin(); i < numbers.cend() - 1; i+=2) {
        std::cout << *i << " + " << *(i+1) << " = " << *i + *(i+1) << std::endl;
    }

    std::cout << "Printing the sum of first <> last pairs...\n";
    auto num1 = numbers.cbegin(), num2 = numbers.cend() - 1;
    while (num1 < num2) {
        std::cout << *num1 << " + " << *num2 << " = " << *num1 + *num2 << std::endl;
        ++num1;
        --num2;
    }
}
