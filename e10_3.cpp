#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>

int main()
{
    std::vector<int> ivec;

    for (int i = 0; i < 10; ++i) {
        ivec.push_back(rand() % 10);
        std::cout << ivec.back() << std::endl;
    }

    auto sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
    std::cout << "sum : " << sum << std::endl;
}
