// Exercise 10.28: Copy a vector that holds the values from 1 to 9 inclusive,
// into three other containers. Use an inserter, a back_inserter, and a
// front_inserter, respectivly to add elements to these containers. Predict
// how the output sequence varies by the kind of inserter and verify your
// predictions by running your programs.

#include <iostream>
#include <vector>
#include <iterator>
#include <list>

int main()
{
    std::vector<int> ivec, ivec1, ivec2;
    std::list<int> ivec3;

    for (int i = 1; i <= 9; ++i) {
        ivec.push_back(i);
    }

    for (auto i:ivec) std::cout << i << " ";
    std::cout << std::endl;

    copy(ivec.cbegin(), ivec.cend(), inserter(ivec1, ivec1.begin()));
    copy(ivec.cbegin(), ivec.cend(), back_inserter(ivec2));
    copy(ivec.cbegin(), ivec.cend(), front_inserter(ivec3));

    for (auto i:ivec1) std::cout << i << " ";
    std::cout << std::endl;

    for (auto i:ivec2) std::cout << i << " ";
    std::cout << std::endl;

    for (auto i:ivec3) std::cout << i << " ";
    std::cout << std::endl;
}
