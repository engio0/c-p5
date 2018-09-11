#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<unsigned> scores(11, 0);
    unsigned grade;

    std::cout << "Enter grades :\n";

    while (std::cin >> grade) {
        if (grade <=100)
            ++scores[grade/10];
    }

    for (auto i = scores.begin(); i < scores.end(); ++i)
        std::cout << *i << std::endl;
}
