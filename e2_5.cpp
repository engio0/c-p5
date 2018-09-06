#include <iostream>

int main()
{
    std::cout << sizeof('a') << ", " << sizeof(L'a') << ", "
        << sizeof("a") << ", " << sizeof(L"a") << std::endl;
    std::cout << sizeof(10) << ", " << sizeof(10u) << ", " << sizeof(10L) << ", "
        << sizeof(10uL) << ", " << sizeof(10LL) << ", " << 012 << ":" << sizeof(012) << ", " 
        << 0xC << ":" << sizeof(0xc) << std::endl;
    std::cout << sizeof(3.14) << ", " << sizeof(3.14f) << ", " << sizeof(3.14L)
        << ", " << std::endl;
    std::cout << sizeof(10) << ' ' << sizeof(10u) << ' ' << sizeof(10.) << ' ' << sizeof(10e-2) << std::endl;
}
