#include <iostream>

int main()
{
    const char *cp[] = "This is const string literal";

    std::cout << *cp << std::endl;
}
