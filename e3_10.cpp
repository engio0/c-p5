/*
 * Exercise 3.10: Write a program that reads a string of characters including
 * punctuation and writes what was read but with the punctuation removed.
 */

#include <iostream>
#include <string>

int main()
{
    std::string buffer, result;

    std::cout << "Enter your input : \n";
    getline(std::cin, buffer);
    
    for (auto c : buffer) {
        if (!ispunct(c)) {
            result += c;
        }
    }

    std::cout << result;
}
