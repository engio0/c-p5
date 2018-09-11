/* Exercise 3.4: Write a program to read two strings and report whether the
 * strings are equal. If not, report which of the two is larger. Now, change
 * the program to report whether the strings have the same length, and if
 * not, report which is longer.
 */

#include <iostream>
#include <string>

int main()
{
    std::string str1, str2;

    std::cout << "Enter the first string : \n";
    std::getline(std::cin, str1);
    std::cout << "Enter the second string : \n";
    std::getline(std::cin, str2);

    if (str1 == str2)
        std::cout << "Two strings are equal!\n";
    else {
        std::string ans;
        ans = (str1 > str2 ? "Str1 > Str2\n" : "Str1 < Str2\n");
        std::cout << "Result 1 : " << ans << std::endl;
    }

    if (str1.size() == str2.size())
        std::cout << "Two strings are of same size!\n";
    else {
        std::string ans;
        ans = (str1.size() > str2.size() ? "Str1.size() > Str2.size()\n" : "Str1.size() < Str2.size()\n");
        std::cout << "Result 2 : " << ans << std::endl;
    }

    return 0;
}
