#include <iostream>
#include <vector>

int main()
{
    std::vector<int> ivec;

    for(int i = 0; i < 10; ++i)
        ivec.push_back(i);
    std::cout << *((ivec.begin)()) << std::endl;
    std::cout << (*((ivec.begin)())) + 1;
}
