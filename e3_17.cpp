/*
 * Exercise 3.17: Read a sequence of words from cin and store the values a
 * vector. After you¡¯ve read all the words, process the vector and change
 * each word to uppercase. Print the transformed elements, eight words to a
 * line.
 */

#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string word;
    std::vector<std::string> table;

    std::cout << "Enter words:\n";

    while (std::cin >> word) {
        table.push_back(word);
    }

    std::cout << "Tranforming to upper case...\n";

    for (auto &w : table) {
        for (auto &c : w) {
            c = toupper(c);
        }
    }

    std::cout << "Transformaiton complete !!!\n";

    for (auto w : table)
        std::cout << w << " ";
    std::cout << "\n<< End Of Transmission >>\n";
}
