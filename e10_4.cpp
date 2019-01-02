#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    std::vector<double> vd = { 1.1, 0.5, 3.3 };

    std::cout << accumulate(vd.cbegin(), vd.cend(), 0) << std::endl;
    std::cout << accumulate(vd.cbegin(), vd.cend(), 0.0) << std::endl;
}
