/*
 * Exercise 3.13: How many elements are there in each of the following
 * vectors? What are the values of the elements?
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1;                 // no element
    vector<int> v2(10);             // 10 int elements with value of 0
    vector<int> v3(10, 42);         // 10 int elements with value of 42
    vector<int> v4{10};             // one int element with value of 10
    vector<int> v5{10, 42};         // two int element with value of 10 and 42
    vector<string> v6{10};          // ten empty string elements
    vector<string> v7{10, "hi"};    // ten string elements with value "hi"
}
