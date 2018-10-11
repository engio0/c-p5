#include <iostream>
#include <stdexcept>

int main()
{
    int val1, val2, result;
    std::cout << "Enter two integers for divition\n";
    std::cin >> val1 >> val2;
    if (val2 == 0)
        throw std::runtime_error("divided by zero");
    result = val1 / val2;
    std::cout << val1 << " / " << val2 << " = " << result << '\n';
}
