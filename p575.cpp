#include <iostream>

int main()
{
    int i, *pi1 = &i, *pi2 = nullptr;
    std::cout << "i = " << i << ", pi1 = " << pi1 << ", pi2 = " << pi2 << std::endl;
    double *pd = new double(33), *pd2 = pd;
//    delete i;
    delete pi1;
    delete pd;
    delete pd2;
    delete pi2;

    const int *pci = new const int(1024);
    delete pci;
}
