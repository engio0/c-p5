#include <iostream>

int compare(const int v1, const int *pv2)
{
    return (v1 >= *pv2 ? v1 : *pv2);
}

int main()
{
    int v1, v2;
    int *pv = &v2;

    for (int i = 0; i < 10; ++i) {
        v1 = rand(), v2 = rand();
        std::cout << v1 << ", " << v2 << " : "
                  << compare(v1, pv) << std::endl;
    }
}
