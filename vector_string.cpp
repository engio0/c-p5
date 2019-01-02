#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> strvec;
    strvec.push_back("first");
    strvec.push_back("second");
    strvec.push_back("third");

    for (auto x:strvec) {
        std::cout << x << std::endl;
    }
}
