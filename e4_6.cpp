#include <iostream>
#include <bitset>

int main()
{
    for (int i = 0; i < 20; ++i) {
        std::cout << std::bitset<4>(i) << std::endl;
    }

    int val;
    while (true) {
    std::cout << "Enter an integer : ";
        std::cin >> val;
        if (std::cin.fail()) {
            std::cout << "Not an integer value!!\n";
            return 1;
        }
        std::cout << (val % 2 ? "Odd value\n" : "Even value\n");
        std::cout << (val & 1) << '\n';
        std::cout << ( val & 0x1 ? "Odd!\n" : "Even!\n");
    }
}
