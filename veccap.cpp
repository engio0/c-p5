#include <iostream>
#include <vector>

int main()
{
    std::vector<int> ivec;

    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    for (std::vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);
    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;
    ivec.reserve(50);
    std::cout << "after ivec.reserve(50)\n";
    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    while (ivec.size() != ivec.capacity())
        ivec.push_back(0);
    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    ivec.push_back(42);
    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;
    ivec.shrink_to_fit();
    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;
}
