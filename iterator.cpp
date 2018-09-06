#include <iostream>
#include <vector>

int main()
{
    std::vector<int> tab;

    tab.push_back(666);
    tab.push_back(999);

    auto b = tab.begin(), e = tab.end();

    std::cout << "sizeof(iterator) : " << sizeof(b) << ", " << sizeof(e) << std::endl;
//    std::cout << "tab.begin() : " << b << ", " << "tab.end() : " << e << std::endl;
    std::cout << "tab.end()-tab.begin() : " << tab.end()-tab.begin();
}
