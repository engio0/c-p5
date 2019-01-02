#include <iostream>
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
