#include <iostream>
#include <map>
#include <string>

int main()
{
    std::multimap<int, std::string> numbers;
    numbers.insert({1, "one"});
    numbers.insert({2, "two"});
    numbers.insert({3, "three"});
    numbers.insert({2, "zwei"});
    numbers.insert({1, "one"});

    for (auto n:numbers) {
        std::cout << n.first << " : " << n.second << std::endl;
    }
}
