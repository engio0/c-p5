#include <iostream>
#include <memory>

int gvar = 1;

int main()
{
    static int slvar = 2;
    int lvar = 3;

    int *dvar = new int(4);

    std::cout << "global : " << &gvar << std::endl;
    std::cout << "local static : " << &slvar << std::endl;
    std::cout << "local : " << &lvar << std::endl;
    std::cout << "dynamic : " << dvar << std::endl;
    std::cout << "main : " << (void*)main << std::endl;
}
