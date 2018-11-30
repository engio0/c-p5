#include <iostream>
#include <vector>

int main()
{
    std::vector<int> ivec = {3, 1, 4, 1, 5, 9};

    std::cout << ivec[0] << " " << ivec.at(0) << " "
              << ivec.front() << " " << *ivec.begin();
}
