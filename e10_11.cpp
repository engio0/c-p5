// Exercise 10.11: Write a program that uses stable_sort and isShorter
// to sort a vector passed to your version of elimDups. Print the vector to
// verify that your program is correct.
//
// the quick red fox jumps over the slow red turtle

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isShorter(const std::string &str1, const std::string &str2)
{
    return str1.size() < str2.size();
}

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

int main()
{
    std::vector<std::string> words{ "the", "quick", "red", "fox", "jumpes", "over",
                                    "the", "slow", "red", "turtle"};

    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);

    for (auto x:words) std::cout << x << " ";
}
