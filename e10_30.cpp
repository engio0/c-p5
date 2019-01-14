// Exercise 10.30: Use stream iterators, sort, and copy to read a sequence
// of integers from the standard input, sort them, and then write them back to
// the standard output.

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main()
{
    std::istream_iterator<int> isi(std::cin), eof;
    std::vector<int> ivec;
    copy(isi, eof, back_inserter(ivec));
    // preceding 3 lines of code can be simplified as the following one line...
    // std::vector<int> vec(std::istream_iterator<int>(std::cin), std::istream_iterator<int>());
    sort(ivec.begin(), ivec.end());
    copy(ivec.cbegin(), ivec.cend(), std::ostream_iterator<int>(std::cout, " "));
}
