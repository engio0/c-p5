// Exercise 10.29: Write a program using stream iterators to read a text file
// into a vector of strings.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " file\n";
        return 1;
    }
    std::ifstream ifile(argv[1]);
    if (!ifile.is_open()) {
        std::cout << "failed to open \"" << argv[1] << "\"\n";
        return 1;
    }

    std::vector<std::string> svec;
    std::istream_iterator<std::string> isi(ifile), eof;
    std::copy(isi, eof, back_inserter(svec));

    copy(svec.cbegin(), svec.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
