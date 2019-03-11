#include <iostream>

int main()
{
    int ival = 666;
    std::cout << "int ival = 666; &ival = " << &ival << std::endl;

    auto p1 = new auto(ival);
    std::cout << "auto p1 = new auto(ival); p1 = " << p1 << std::endl;
    std::cout << "*p1 = " << *p1 << std::endl;

    auto p2 = new decltype(ival);
    std::cout << "auto p2 = new auto(ival); p2 = " << p2 << std::endl;
    std::cout << "*p2 = " << *p2 << std::endl;

    for (int i = 1; ; ++i) {
        std::cout << "\nAllocating 8 Gigs... " << i << "\n";
        char *ph = new (std::nothrow) char[1000000000];
        if (!ph) {
            std::cout << "Allocation Failed !!!\n";
            return 1;
        }
    }
}
