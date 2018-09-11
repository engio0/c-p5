#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v2;

    for (int i = 0; i != 100; ++i)
        v2.push_back(i);

    for (int i : v2)
        std::cout << v2[i] << " ";

    std::cout << "\nsizeof(v2) : " << sizeof(v2) << std::endl;
    std::cout << "v2.size() : " << v2.size() << std::endl;
}
