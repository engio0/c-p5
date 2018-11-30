#include <iostream>
#include <vector>

int main()
{
    std::vector<int> iv;
    std::cout << "initial size() : " << iv.size() << std::endl;
    std::cout << "initial capacity() : " << iv.capacity() << std::endl;
    iv.reserve(10);
    std::cout << "after reserve(10), capacity() : " << iv.capacity() << std::endl;
    iv.shrink_to_fit();
    std::cout << "after shrink_to_fit(), capacity() : " << iv.capacity() << std::endl;

    std::vector<int>::size_type capa = 0;
    for (int i = 0; i < 65535; ++i) {
        iv.push_back(i);
        if (iv.capacity() != capa) {
            std::cout << "at size() : " << iv.size() << ", ";
            std::cout << "capacity() changed to " << iv.capacity() << std::endl;
//        std::cout << "after push_back(" << i << "), capacity() : " << iv.capacity() << std::endl;
            capa = iv.capacity();
        }
    }
}
