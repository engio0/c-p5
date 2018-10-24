#include <vector>

int func(int, int);
std::vector<decltype(func)*> vecfunc;
std::vector<int(*)(int, int)> vecfunc2;
