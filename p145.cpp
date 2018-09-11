#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> v1(10);
    std::vector<int> v2{10};
    std::vector<int> v3(10, 1);
    std::vector<int> v4{10, 1};

    std::vector<std::string> v5{"hi"};
    std::vector<std::string> v6("hi");
    std::vector<std::string> v7{10};
    std::vector<std::string> v8{10, "hi"};
}
