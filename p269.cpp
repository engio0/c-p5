#include <iostream>

int fact(int val)
{
    int ret = 1;
    while (val > 1) {
        ret *= val--;
    }
    return ret;
}

int main()
{
    for (int i = 2; i < 6; ++i) {
        std::cout << "fact(" << i << ") = ";
        std::cout << fact(i) << std::endl;
    }
}
