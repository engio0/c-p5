/*
 * Exercise 3.16: Write a program to print the size and contents of the
 * vectors from exercise 3.13. Check whether your answers to that exercise
 * were correct. If not, restudy § 3.3.1 (p. 97) until you understand why you
 * were wrong.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1;                 // no element
    std::cout << "v1.size() : " << v1.size() << "\nv1 contains :\n";
    for (int i = 0; i < v1.size(); ++i)
        std::cout << "v1[" << i << "] : " << v1[i] << std::endl;

    vector<int> v2(10);             // 10 int elements with value of 0
    std::cout << "v2.size() : " << v2.size() << "\nv2 contains :\n";
    for (int i = 0; i < v2.size(); ++i)
        std::cout << "v2[" << i << "] : " << v2[i] << std::endl;

    vector<int> v3(10, 42);         // 10 int elements with value of 42
    std::cout << "v3.size() : " << v3.size() << "\nv3 contains :\n";
    for (int i = 0; i < v3.size(); ++i)
        std::cout << "v3[" << i << "] : " << v3[i] << std::endl;

    vector<int> v4{10};             // one int element with value of 10
    std::cout << "v4.size() : " << v4.size() << "\nv4 contains :\n";
    for (int i = 0; i < v4.size(); ++i)
        std::cout << "v4[" << i << "] : " << v4[i] << std::endl;

    vector<int> v5{10, 42};         // two int element with value of 10 and 42
    std::cout << "v5.size() : " << v5.size() << "\nv5 contains :\n";
    for (int i = 0; i < v5.size(); ++i)
        std::cout << "v5[" << i << "] : " << v5[i] << std::endl;

    vector<string> v6{10};          // ten empty string elements
    std::cout << "v6.size() : " << v6.size() << "\nv6 contains :\n";
    for (int i = 0; i < v6.size(); ++i)
        std::cout << "v6[" << i << "] : " << v6[i] << std::endl;

    vector<string> v7{10, "hi"};    // ten string elements with value "hi"
    std::cout << "v7.size() : " << v7.size() << "\nv7 contains :\n";
    for (int i = 0; i < v7.size(); ++i)
        std::cout << "v7[" << i << "] : " << v7[i] << std::endl;
}
