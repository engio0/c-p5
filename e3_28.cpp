// Exercise 3.28: What are the values in the following arrays?
// 
// string sa[10];
// int ia[10];
// 
// int main() {
//     string sa2[10];
//     int ia2[10];
// }

#include <iostream>
#include <string>
using std::string;

string sa[10];
int ia[10];

int main() {
    string sa2[10];
    int ia2[10];

    for (auto i:sa)
        std::cout << i << ":";
    std::cout << std::endl;

    for (auto i:ia)
        std::cout << i << ":";
    std::cout << std::endl;

    for (auto i:sa2)
        std::cout << i << ":";
    std::cout << std::endl;

    for (auto i:ia2)
        std::cout << i << ":";
    std::cout << std::endl;
}
