#include <iostream>
#include <iterator>

int main()
{
    int arr[11];

    for (int *parr = arr; parr != std::end(arr); ++parr) {
        *parr = 0;
    }

    for (auto i:arr) std::cout << i << " ";
}
