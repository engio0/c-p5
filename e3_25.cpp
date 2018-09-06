// Exercise 3.25: Rewrite the grade clustering program from ¡× 3.3.3 (p. 104)
// using iterators instead of subscripts.

#include <iostream>
#include <vector>

int main()
{
    std::vector<unsigned> scores(11, 0);
    auto sector = scores.begin();
    unsigned grade;

    std::cout << "Enter grades...\n";

    while (std::cin >> grade) {
        if (grade <= 100)
            ++*(sector + grade/10);
    }

    for (auto i:scores) {
        std::cout << i << " ";
    }
}
