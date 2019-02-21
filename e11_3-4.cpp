// Exercise 11.3: Write your own version of the word-counting program.
//
// Exercise 11.4: Extend your program to ignore case and punctuation. For
// example, “example.” “example,” and “Example” should all increment the same
// counter.


#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cctype>

std::string to_upper_str(std::string const & str)
{
    std::string upper;
    for (auto c:str) {
        upper.push_back(toupper(c));
    }
    return upper;
}

int main()
{
    std::map<std::string, size_t> word_count, ciword_count;
    std::set<std::string> exclude = {"The", "But", "And", "Or", "An", "A",
                                     "the", "but", "and", "or", "an", "a"};
    std::string word;
    char ch;

    while (std::cin.get(ch)) {
        if (isalnum(ch)) {
            word.push_back(ch);
//            std::cout << "push back : \"" << ch << "\"";
            continue;
        }
        if (word.size()) {
            ++word_count[word];
//            std::cout << "registered : " << word << std::endl;
            ++ciword_count[to_upper_str(word)];
            word.clear();
        }
    }

    for (const auto &w : word_count) {
        std::cout << w.first << " occurs " << w.second
                  << ( (w.second > 1) ? " times" : " time" ) << std::endl;
    }
    std::cout << "********** word count : " << word_count.size() << std::endl;

    for (const auto &w : ciword_count) {
        std::cout << w.first << " occurs " << w.second
                  << ( (w.second > 1) ? " times" : " time" ) << std::endl;
    }
    std::cout << "********** ci word count : " << ciword_count.size() << std::endl;
}
