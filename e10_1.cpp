#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

int main()
{
    std::vector<int> ivec;

    for (int i = 0; i < 100; ++i) {
       ivec.push_back(rand() % 10);
    }

    for (int i = 0; i < 16; ++i) {
        std::cout << i << "\t: " << count(ivec.cbegin(), ivec.cend(), i) << std::endl;
    }
}
