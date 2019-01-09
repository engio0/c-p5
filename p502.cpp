#include <functional>
#include <string>
#include <vector>
#include <algorithm>

bool check_size(const std::string &s, std::string::size_type sz)
{
    return s.size() >= sz;
}

int main()
{
    std::vector<std::string> words {"hello", "world", "i will", "escape", "from", "this", "cruel", "world"};
    size_t sz = 5;
    auto wc = find_if(words.begin(), words.end(), bind(check_size, std::placeholders::_1, sz));
}
