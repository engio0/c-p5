#include <map>
#include <set>
#include <string>

int main()
{
    std::map<std::string, size_t> word_count;
    std::set<std::string> exclude = {"the", "but", "and", "or", "an", "a",
                                     "The", "But", "And", "Or", "An", "A"};
    std::map<std::string, std::string> authors = { {"Joyce", "James"},
                                                   {"Austen", "Jane"},
                                                   {"Dickens", "Charles"} };
}
