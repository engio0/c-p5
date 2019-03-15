// Exercise 12.16: Compilers don’t always give easy-to-understand error
// messages if we attempt to copy or assign a unique_ptr. Write a program
// that contains these errors to see how your compiler diagnoses them.

#include <iostream>
#include <memory>
#include <string>

int main()
{
    std::unique_ptr<std::string> p1(new std::string("Hello"));
    std::unique_ptr<std::string> p2(p1);
    std::unique_ptr<std::string> p3 = p1;

    std::cout << *p1 << '\n';
}
