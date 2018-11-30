#include <forward_list>
#include <string>

void func(std::forward_list<std::string> &slst, const std::string &sfind, const std::string &sinj)
{
    auto prev = slst.before_begin();
    auto curr = slst.begin();

    while (curr != slst.end()) {
        if (*curr == sfind) break;
        prev = curr;                    // prev = curr++
        ++curr;                         //
    }
    slst.insert_after(curr, sinj);
}
