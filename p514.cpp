#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int main()
{
    std::istringstream vec {"0 1 2 3 4 5 6 7 8 9"};
    std::vector<int> ivec;
    int ibuf;

    while (vec >> ibuf) {
        ivec.push_back(ibuf);
    }

    sort(ivec.rbegin(), ivec.rend());

    for (auto i:ivec) std::cout << i << " ";
}
