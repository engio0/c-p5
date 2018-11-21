#include <iostream>
#include <array>

int main()
{
    int num;
    std::cout << "Enter the number of array : \n";
    std::cin >> num;

    std::array<int, 10> arr;
    for (int i = 0; i < num; ++i) {
        arr[i] = i;
    }

    for (auto x:arr) {
        std::cout << arr[x] << " ";
    }
}
