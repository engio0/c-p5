#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main()
{
    std::istream_iterator<int> in_iter(std::cin), eof;
//    std::vector<int> vec(in_iter, eof);                 // construct vec from an iterator range
//    for (auto i:vec) std::cout << i << " ";

    std::cout << '\n' << accumulate(in_iter, eof, 0) << std::endl;
}
