#include <iostream>

int main()
{
    int ival = ~'q' << 6;

    for (int i = 0; i < 32; ++i) {
        std::cout << ( (ival & ((1UL << 31) >> i)) ? "1" : "0" );
    }

    std::cout << " : " << ival << std::endl;
    std::cout << "1UL << 31 : " << (1UL<<31) << std::endl;
}
