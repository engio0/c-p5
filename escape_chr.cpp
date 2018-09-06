#include <iostream>
#include <ctype.h>

int main()
{
    std::cout << "This effect is from the carriage return\r!!!" << std::endl;
    std::cout << "isspace('\f') = " << isspace('\f') << std::endl;
    std::cout << "This effect is from the form feed\f!!!" << std::endl;

    return 0;
}
