#include <iostream>
#include <string>
#include <deque>

int main()
{
    std::string buffer;
    std::deque<std::string> book;
    while (std::cin >> buffer) {
        book.push_back(buffer);
    }

    for (auto x = book.begin(); x != book.end(); ++x) {
        std::cout << *x << std::endl;
    }
}
