// Exercise 12.6: Write a function that returns a dynamically allocated vector
// of ints. Pass that vector to another function that reads the standard input
// to give values to the elements. Pass the vector to another function to print
// the values that were read. Remember to delete the vector at the
// appropriate time.#include <iostream>

#include <vector>

std::vector<int> *alloc()
{
    return new std::vector<int>;
}

int main()
{
}
