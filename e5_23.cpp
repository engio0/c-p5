#include <iostream>

int main()
{
    int val1, val2, result;
    std::cout << "Enter two integers for divition\n";
    std::cin >> val1 >> val2;
    result = val1 / val2;
    std::cout << val1 << " / " << val2 << " = " << result << '\n';
}
