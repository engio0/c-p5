#include <iostream>
#include <iomanip>

int main()
{
    char cval = 0;

    do {
        std::cout << std::setw(4) << (int)cval << " : ";
        for (int i = 7; i >= 0; --i) {
            std::cout << ( ((cval >> i) % 2) ? "1" : "0" );
        }
        std::cout << std::endl;
        ++cval;
    } while (cval);
}
