#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int main()
{
    std::vector<int> ivec;

    std::srand(std::time(0));

    for (int i = 0; i < 10; ++i) {
        ivec.push_back(std::rand());
        std::cout << std::setw(6) << ivec.back() << " : " <<
            (ivec.back() % 2 ? "Odd" : "Even") << '\n';
    }

}
