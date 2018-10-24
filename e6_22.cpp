#include <iostream>

void swap_ptr(int *&pv1, int *&pv2)
{
    int *tmp = pv1;
    pv1 = pv2, pv2 = tmp;
}

int main()
{
    int a = 33, b = 66;
    int *pa = &a, *pb = &b;
    std::cout << *pa << ", " << *pb << " @ ";
    std::cout << pa << ", " << pb << std::endl;

    swap_ptr(pa, pb);

    std::cout << *pa << ", " << *pb << " @ ";
    std::cout << pa << ", " << pb << std::endl;
}
