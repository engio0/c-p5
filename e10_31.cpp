// Exercise 10.31: Update the program from the previous exercise so that it
// prints only the unique elements. Your program should use unqiue_copy (§
// 10.4.1, p. 403).
//
// Exercise 10.30: Use stream iterators, sort, and copy to read a sequence
// of integers from the standard input, sort them, and then write them back to
// the standard output.

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main()
{
//    std::istream_iterator<int> isi(std::cin), eof;
//    std::vector<int> ivec;
//    copy(isi, eof, back_inserter(ivec));
    // preceding 3 lines of code can be simplified as the following one line...
    std::vector<int> ivec((std::istream_iterator<int>(std::cin)), std::istream_iterator<int>());
    sort(ivec.begin(), ivec.end());
    unique_copy(ivec.begin(), ivec.end(), std::ostream_iterator<int>(std::cout, " "));
}
