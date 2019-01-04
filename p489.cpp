#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// bool isShorter(const std::string &str1, const std::string &str2)
// {
//     return str1.size() < str2.size();
// }

std::string make_plural(size_t ctr, const std::string &word, const std::string &ending)
{
    return (ctr > 1) ? word + ending : word;
}

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(std::vector<std::string> &words,
             std::vector<std::string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), [](const std::string &a, const std::string &b)
                                            { return a.size() < b.size(); });
    auto wc = find_if(words.cbegin(), words.cend(), [sz] (const std::string &a)
                                               { return a.size() >= sz; });
    auto count = words.cend() - wc;
    std::cout << count << " " << make_plural(count, "word", "s")
              << " of length " << sz << " or longer" << std::endl;
    for_each(wc, words.cend(), [](const std::string &s){ std::cout << s << " "; });
    std::cout << std::endl;
}

void biggies1(std::vector<std::string> &words,
             std::vector<std::string>::size_type sz)
{
    elimDups(words);

    auto wc = partition(words.begin(), words.end(), [sz](std::string &s){ return s.size() < sz; });
    auto count = words.cend() - wc;
    std::cout << count << " " << make_plural(count, "word", "s")
              << " of length " << sz << " or longer" << std::endl;
    for_each(wc, words.end(), [](const std::string &s){ std::cout << s << " "; });
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> str0{"This", "is", "strings", "of", "a", "sentence."};
    biggies(str0, 4);
    biggies1(str0, 4);
}
