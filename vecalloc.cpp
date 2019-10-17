#include <iostream>
#include <iomanip>
#include <vector>

int main(int, char*[])
{
    std::vector<int> ivec;
    std::cout << "Initial address : " << &ivec
              << ", size : " << ivec.size()
              << ", capacity : " << ivec.capacity() << std::endl;

    for (int i = 0; i < 100; ++i) {
        ivec.push_back(i);
        std::cout << std::setw(6) << i << " @ " << &ivec
                  << ", size : " << ivec.size()
                  << ", capacity : " << ivec.capacity() << std::endl;
    }

    return 0;
}
