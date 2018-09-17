#include <iostream>
#include <iomanip>

int main()
{
    int ia[3][4];
    int *ip = (int*)ia;

    std::cout << "ia : " << ia << '\n';

    for (int i = 0; i < 12; ++i) {
        *(ip + i) = i;
        std::cout << "ip + i : " << ip + i << ", *(ip + i) : " << std::setw(2) << *(ip + i) << '\n';
    }

    using int_array = int[4];
    typedef int int_array[4];

    for (int_array *p = ia; p != ia + 3; ++p) {
        for (int *q = *p; q != *p + 4; ++q) {
            std::cout << *q << ' ';
        }
        std::cout << std::endl;
    }
}
