// Exercise 9.49: A letter has an ascender if, as with d or f, part of the letter
// extends above the middle of the line. A letter has a descender if, as with p or
// g, part of the letter extends below the line. Write a program that reads a file
// containing words and reports the longest word that contains neither
// ascenders nor descenders.

#include <iostream>
#include <fstream>
#include <string>

int count_ascdesc(const std::string &word)
{
    const std::string ascdesc("bdfhklgjpqy");
    int cnt = 0;
    std::string::size_type pos = 0;

    while ((pos = word.find_first_not_of(ascdesc, pos)) != std::string::npos) {
        ++cnt;
        ++pos;
    }
    return cnt;
}

bool hasAscDesc(const std::string &word)
{
    const std::string ascdesc("bdfhklgjpqy");
    if (word.find_first_of(ascdesc) != std::string::npos) return true;
    return false;
}

int main(int argc, char *argv[])
{
    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " filename\n"
                  << "Input file can be pipelined from standard input stream\n";
        return 1;
    }
    std::ifstream input;
    std::streambuf *orig_cin = 0;
    if (argc == 2) {
        input.open(argv[1]);
        if (!input) {
            std::cout << "file \"" << argv[1] << "\" can not be opened!!!\n";
            return 1;
        }
        orig_cin = std::cin.rdbuf(input.rdbuf());
        std::cin.tie(0);
    }

    std::string::size_type cntLongest = 0;
    std::string wordLongest;
    std::string buffer;

    while (std::cin >> buffer) {
//        std::cout << buffer << " : ";
        if (!hasAscDesc(buffer)) {
//            std::cout << " no AscDesc : ";
            if (buffer.size() > cntLongest) {
                wordLongest = buffer;
                cntLongest = buffer.size();
//                std::cout << "size : " << buffer.size();
            }
        }
//        std::cout << std::endl;
    }
    std::cout << "The longest word without ascend or descend is : " << wordLongest << std::endl;
}
