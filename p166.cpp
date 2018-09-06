#include <iostream>

int main()
{
    unsigned scores[11] = {};
    unsigned grade;

    while (std::cin >> grade) {
        if (grade <= 100)
            ++scores[grade/10];
    }

    for (auto i:scores)
        std::cout << i << " ";
}
