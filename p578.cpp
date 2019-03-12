#include <iostream>

int main()
{
    int *p(new int(42));
    auto q = p;
    std::cout << "p = " << p << ", q = " << q << std::endl;
    std::cout << "*p = " << *p << ", *q = " << *q << std::endl;
    delete p;
    p = nullptr;

    int *p1{new int(63)};
    std::cout << "p1 = " << p1 << ", *pi = " << *p1 << std::endl;
}
