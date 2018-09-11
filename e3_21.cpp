/*
 * Exercise 3.21: Redo the first exercise from § 3.3.3 (p. 105) using iterators.
 *
 * Exercise 3.16: Write a program to print the size and contents of the
 * vectors from exercise 3.13. Check whether your answers to that exercise
 * were correct. If not, restudy § 3.3.1 (p. 97) until you understand why you
 * were wrong.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void enumerate(const vector<int>& vec)
{
    std::cout << "size : " << vec.size() << std::endl;
    for (auto i = vec.cbegin(); i != vec.cend(); ++i) {
        std::cout << *i << (i == vec.cend() - 1 ? "\n" : " ");
    }
}

void enumerate(const vector<string>& vec)
{
    std::cout << "size : " << vec.size() << std::endl;
    for (auto i = vec.cbegin(); i != vec.cend(); ++i) {
        std::cout << *i << (i == vec.cend() - 1 ? "\n" : " ");
    }
}

int main()
{
    vector<int> v1;                 // no element
    vector<int> v2(10);             // 10 int elements with value of 0
    vector<int> v3(10, 42);         // 10 int elements with value of 42
    vector<int> v4{10};             // one int element with value of 10
    vector<int> v5{10, 42};         // two int element with value of 10 and 42
    vector<string> v6{10};          // ten empty string elements
    vector<string> v7{10, "hi"};    // ten string elements with value "hi"

    enumerate(v1);
    enumerate(v2);
    enumerate(v3);
    enumerate(v4);
    enumerate(v5);
    enumerate(v6);
    enumerate(v7);
}
