#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> story = {"the", "quick", "red", "fox", "jumps", "over",
                                    "the", "slow", "red", "turtle"};
    std::cout << "size of story : " << story.size() << std::endl;

    for (auto x:story) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;

    std::sort(story.begin(), story.end());
    for (auto x:story) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;

    auto end_unique = std::unique(story.begin(), story.end());
    for (auto x:story) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;

    story.erase(end_unique, story.end());
    for (auto x:story) {
        std::cout << x << ", ";
    }
}
