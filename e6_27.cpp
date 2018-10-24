#include <iostream>
#include <initializer_list>

int sum(const std::initializer_list<int>&ilist)
{
    int result = 0;

    for (auto val:ilist) {
        result += val;
    }
    std::cout << "The sum is " << result << std::endl;
    return result;
}

int main()
{
    std::cout << "in main, sum is " << sum({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}
