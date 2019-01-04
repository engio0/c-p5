#include <iostream>

int main()
{
    std::cout << "Enter two integers..\n";
    int i1, i2;
    std::cin >> i1 >> i2;

    auto add = [](int a1, int a2){return a1 + a2;};
    std::cout << add(i1, i2);
}
