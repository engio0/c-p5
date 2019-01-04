#include <iostream>

int main()
{
    int local = 36;
    int argum = 63;

    auto add = [local](int ar){ return local + ar; };
    std::cout << add(argum); 
}
