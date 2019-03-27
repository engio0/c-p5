#include <iostream>

int main()
{
    int *pia = new int[10]();

    for (auto i = 0; i < 10; ++i) {
        std::cout << pia[i] << " ";
    }
}
