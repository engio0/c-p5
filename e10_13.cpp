// Exercise 10.13: The library defines an algorithm named partition that
// takes a predicate and partitions the container so that values for which theinclude <iostream>
// predicate is true appear in the first part and those for which the predicate is
// false appear in the second part. The algorithm returns an iterator just past
// the last element for which the predicate returned true. Write a function that
// takes a string and returns a bool indicating whether the string has five
// characters or more. Use that function to partition words. Print the elements
// that have five or more characters.

#include <vector>
#include <string>
#include <algorithm>

bool hasFive(const std::string word)
{
    return (word.size() >= 5);
}

int main()
{
    std::vector<std::string> words{ "the", "quick", "red", "fox", "jumpes", "over",
                                    "the", "slow", "red", "turtle"};

    auto part = std::partition(words.begin(), words.end(), hasFive);

    std::cout << "The following words has 5 or more chars\n";
    for (auto i = words.cbegin(); i != part; ++i) {
        std::cout << *i << std::endl;
    }

    std::cout << "The following words has 4 or less chars\n";
    for (auto i = part; i != words.cend(); ++i) {
        std::cout << i[0] << std::endl;
    }
}
