// Exercise 8.1: Write a function that takes and returns an istream&. The
// function should read the stream until it hits end-of-file. The function should
// print what it reads to the standard output. Reset the stream so that it is valid
// before returning the stream.#include <iostream>

// Exercise 8.9: Use the function you wrote for the first exercise in § 8.1.2 (p.
// 314) to print the contents of an istringstream object.


#include <string>

std::istream& func(std::istream& is)
{
    std::string buf;
    while (std::cin >> buf) {
        std::cout << buf << std::endl;
    }
    is.clear();
    return is;
}

int main()
{
    std::istream& is = func(std::cin);
    std::cout << is.rdstate() << std::endl;
}
