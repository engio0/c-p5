#include <iostream>
#include <string>
#include <list>
#include <vector>

int main()
{
    std::vector<std::string> v = {"quasi", "simba", "frollo", "scar"};
    std::list<std::string> slist;

    slist.insert(slist.begin(), v.end()-2, v.end());
    slist.insert(slist.end(), {"these", "words", "will",
                               "go", "at", "the", "end"});
    
    // run-time error: iterators denoting the range to copy from
    // must not refer to the same container as the one we are changing
    // 그런데, gcc(7.2.0), msvc에서는 에러 없음
    slist.insert(slist.begin(), slist.begin(), slist.end());

    for (auto i:slist) {
        std::cout << i << " ";
    }
}
