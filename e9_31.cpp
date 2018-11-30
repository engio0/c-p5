// Exercise 9.31: The program on page 354 to remove even-valued elements
// and duplicate odd ones will not work on a list or forward_list. Why?
// Revise the program so that it works on these types as well.
// 
// vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
// auto iter = vi.begin();
// while (iter != vi.end()) {
//     if (*iter % 2) {
//         iter = vi.insert(iter, *iter);
//         iter += 2;
//     } else
//         iter = vi.erase(iter);
// }

#include <iostream>
#include <list>
#include <forward_list>

int main()
{
    std::list<int> ilist = {0,1,2,3,4,5,6,7,8,9};
    std::forward_list<int> iflist = {0,1,2,3,4,5,6,7,8,9};

    auto iter1 = ilist.begin();

    while (iter1 != ilist.end()) {
        if (*iter1 % 2) {
            iter1 = ilist.insert(iter1, *iter1);
            ++iter1; ++iter1;
        } else
            iter1 = ilist.erase(iter1);
    }
    std::cout << "finished inserting in ilist\n";
    for (auto x:ilist) std::cout << x;
    std::cout << std::endl;

    auto prev = iflist.before_begin();
    for (auto iter = iflist.begin(); iter != iflist.end();) {
        if (*iter %2) {
            iter = iflist.insert_after(prev, *iter);
            ++iter, ++iter;             // can be replaced with "std::advance(iter, 2);"
            ++prev, prev++;             // ++prev++ DOES NOT WORK!!! because post++ operator returns A COPY!!!
        } else {                        // for the same reason (prev++)++ nor prev++++ does not work!
            iter = iflist.erase_after(prev);
        }
    }
    std::cout << "finished inserting in iflist\n";

    for (auto x:iflist) std::cout << x;
    std::cout << std::endl;
}
