#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main()
{
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::cout << distance(in_iter, eof) << std::endl;
    std::istream_iterator<int> backup = in_iter;
    std::istream_iterator<int> bkeof = eof;
    std::vector<int> vec(in_iter, eof);                 // construct vec from an iterator range
    for (auto i:vec) std::cout << i << " ";
    std::cout << " : size of " << vec.size() << std::endl;

    if (in_iter == backup) std::cout << "\nin_iter = backup of in_iter\n";
    if (bkeof == eof) std::cout << "\nbackup of eof = eof\n";
    std::cout << '\n' << accumulate(in_iter, eof, 0) << std::endl;
    std::vector<int> vec2(in_iter, eof);
    for (auto i:vec2) std::cout << i << " ";

    std::ostream_iterator<int> out_iter(std::cout, " ");
    for (auto o:vec) *out_iter++ = o;
    std::cout << std::endl;
    for (auto o:vec) *out_iter = o;
    std::cout << std::endl;
    for (auto o:vec) out_iter++ = o;
    std::cout << std::endl;
    for (auto o:vec) out_iter = o;
}
