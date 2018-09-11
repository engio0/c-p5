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

    for (auto p = ia; p != ia + 3; ++p) {
        std::cout << "p : " << p << ", *p : " << *p << ", **p : " << **p << '\n';
        for (auto q = *p; q != *p + 4; ++ q) {
            std::cout << "q : " << q << ", *q : ";
            std::cout << std::setw(2) << *q << " | ";
        }
        std::cout << std::endl;
    }
}
