#include <iostream>

int main()
{
    int ia[3][4];
    int arr[10][20][30] = {0};

    for (auto i:ia) {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    for (auto i:arr) {
        std::cout << i << " ";
    }
}
