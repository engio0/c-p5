//  Exercise 3.23: Write a program to create a vector with ten int elements.
//  Using an iterator, assign each element a value that is twice its current value.
//  Test your program by printing the vector.

#include <iostream>
#include <vector>
#include <cstdlib>

int main()
{
    std::cout << "RAND_MAX : " << RAND_MAX << std::endl;

    std::vector<int> numbers;

    for (int i = 0; i < 10; ++i) {
        numbers.push_back( rand() );
    }

    for (auto i = numbers.begin(); i != numbers.end(); ++i) {
        std::cout << *i << " >> ";
        *i *= 2;
        std::cout << *i << std::endl;
    }
}
