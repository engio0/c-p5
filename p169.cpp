#include <iostream>

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "&arr[] : " << &arr << std::endl;

    int *p = arr;
    std::cout << "p : " << p << std::endl;

    ++p;
    std::cout << "++p : " << p << std::endl;

    int *e = &arr[10];
    std::cout << "&arr[10] : " << e << std::endl;

    for (int *b = arr; b != e; ++b)
        std::cout << *b << " @ " << b << std::endl;
}
    
