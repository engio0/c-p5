/* Exercise 3.5: Write a program to read strings from the standard input,
 * concatenating what is read into one large string. Print the concatenated
 * string. Next, change the program to separate adjacent input strings by a
 * space.
 */

#include <iostream>
#include <string>

int main()
{
    std::string total1, total2, buffer;

    while (std::cin >> buffer) {
        total1 += buffer;
        total2 += buffer + ' ';
    }
    std::cout << "total1 : " << total1 << std::endl;
    std::cout << "total2 : " << total2 << std::endl;

    return 0;
}
