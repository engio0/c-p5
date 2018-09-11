#include <iostream>
#include <cstddef>
#include <iterator>

int main()
{
    constexpr size_t sz = 5;
    std::cout << "constexpr size_t sz = 5; &sz : " << &sz << '\n';
    int arr[sz] = {1, 2, 3, 4, 5};
    std::cout << "int arr[sz] = {1, 2, 3, 4, 5}; arr : " << arr << '\n';
    int *ip = arr;
    std::cout << "int *ip = arr; ip : " << ip << '\n';
    int *ip2 = ip + 4;
    std::cout << "int *ip2 = ip + 4; ip2 : " << ip2 << '\n';

    int *p = arr + sz;
    std::cout << "int *p = arr + sz; p : " << p << '\n';
    std::cout << "*p : " << *p << '\n';
    int *p2 = arr + 10;
    std::cout << "int *p2 = arr + 10; p2 : " << p2 << '\n';
    std::cout << "*p2 : " << *p2 << '\n';

    auto n = std::end(arr) - std::begin(arr);
    std::cout << "auto n = end(arr) - begin(arr); n : " << n << '\n';
    std::cout << "begin(arr) : " << std::begin(arr) << ", end(arr) : " << std::end(arr) << '\n';

    int *b = arr, *e = arr + sz;
    while (b < e) {
        std::cout << *b << " ";
        ++b;
    }
    std::cout << '\n' << 3[arr] << std::endl;
}
