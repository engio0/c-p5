// Exercise 8.10: Write a program to store each line from a file in a
// vector<string>. Now use an istringstream to read each element from
// the vector a word at a time.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage : " << argv[0] << " filename\n";
        return 1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << argv[1] << " does not exist !!\n";
        return 1;
    }

    std::ofstream ofs(std::string(argv[1]) + ".word");
    if (!ofs) {
        std::cerr << "Cannot create " << std::string(argv[1]) + ".word\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string buffer;

    while (std::getline(ifs, buffer)) {
        lines.push_back(buffer);
        std::istringstream words(buffer);
        while (words >> buffer) {
            std::cout << buffer << " ";
        }
    }
}
