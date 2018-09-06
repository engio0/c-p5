#include <iostream>
#include <vector>

int main()
{
    int int_arr[] = {0, 1, 2, 3, 4, 5};

    std::vector<int> ivec(std::begin(int_arr), std::end(int_arr));

    std::cout << "ivec.size() = " << ivec.size();
}
