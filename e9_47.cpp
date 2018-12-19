// Exercise 9.47: Write a program that finds each numeric character and then
// each alphabetic character in the string "ab2c3d7R4E6". Write two
// versions of the program. The first should use find_first_of, and the
// second find_first_not_of.

#include <iostream>
#include <string>

int main()
{
    std::string alnum("ab2c3d7R4E6");
    std::string numbers("0123456789");
    std::string alpstr;
    std::string numstr;
    std::string::size_type pos = 0;

    while ((pos = alnum.find_first_of(numbers, pos)) != std::string::npos) {
        numstr.append(alnum, pos, 1);
        ++pos;
    }

    pos = 0;
    while ((pos = alnum.find_first_not_of(numbers, pos)) != std::string::npos) {
        alpstr.append(alnum, pos, 1);
        ++pos;
    }

    std::cout << numstr << " | " << alpstr << std::endl;


    return 0;
}
