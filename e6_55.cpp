#include <vector>
#include <iostream>

int func(int, int);
std::vector<decltype(func)*> vecfunc;
std::vector<int(*)(int, int)> vecfunc2;

int add(int v1, int v2)
{
    return v1 + v2;
}

int sub(int v1, int v2)
{
    return v1 - v2;
}

int mult(int v1, int v2)
{
    return v1 * v2;
}

int divide(int v1, int v2)
{
    if (!v2) return 0;
    return v1 / v2;
}

int main()
{
    std::vector<decltype(func) *> vfn{add, sub, mult, divide};
    vecfunc.assign(add, sub, mult, divide);

    for (auto f:vfn) {
        std::cout << f(2, 2) << std::endl;
    }
}
