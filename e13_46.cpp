#include <vector>
#include <iostream>

int f();

int main()
{
    std::vector<int> vi(100);

    int&& r1 = f();
    int& r2 = vi[0];
    int& r3 = r1;
    int&& r4 = vi[0] * f();

    std::cout << r1 << r2 << r3 << r4;

    return 0;
}
