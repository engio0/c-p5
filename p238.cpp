#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <time.h>

std::string letter_grade(int grade)
{
    std::vector<std::string> scores = {"F", "D", "C", "B", "A", "A++"};
    std::string lettergrade;

    if (grade < 60) {
        lettergrade = scores[0];
    }
    else {
        lettergrade = scores[(grade - 50)/10];
        if (grade % 10 > 7) {
            lettergrade += '+';
        }
        else if (grade % 10 < 3) {
            if (grade != 100) lettergrade += '-';
        }
    }
    return lettergrade;
}

int main()
{
    int grade;

    srand(time(NULL));

    for (int i = 0; i < 20; ++i) {
        grade = std::rand() % 101;
        std::cout << std::setw(4) << grade << " : " << letter_grade(grade) << std::endl;
    }
}
