#include <iostream>
#include <string>
#include <list>

int main()
{
    std::list<std::string> book;
    for (std::string buffer; std::cin >> buffer; book.push_back(buffer));

    for (auto x = book.cbegin(); x != book.cend(); ++x) {
        std::cout << *x << std::endl;
    }
}
