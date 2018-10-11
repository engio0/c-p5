#include <iostream>
#include <stdexcept>

int main()
{
    int val1, val2, result;
    while (true) {
        std::cout << "Enter two integers for divition\n";
        std::cin >> val1 >> val2;
        try
        {
            if (!std::cin)
                throw std::runtime_error("Bad input");
            if (val2 == 0)
                throw std::runtime_error("divided by zero");
            result = val1 / val2;
            std::cout << val1 << " / " << val2 << " = " << result << '\n';
        }
        catch (std::runtime_error err)
        {
            std::cout << "runtime error occured : " << err.what() << '\n';
            std::cout << "Try again?\n";
            char c;
            std::cin >> c;
            if (!std::cin || c == 'n')
                break;
        }
    }
}
