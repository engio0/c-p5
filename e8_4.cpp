#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Usage : " << argv[0] << " filename\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "file name \"" << argv[1] << "\" does not exist!!\n";
        return 1;
    }

    std::vector<std::string> dict;
    std::string buffer;
    while (infile >> buffer) {
        dict.push_back(buffer);
    }

    for (auto word:dict) {
        std::cout << word << std::endl;
    }
}
