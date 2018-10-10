#include <iostream>
#include <string>

int main()
{
    std::string buffer, preval;
    while (std::cin >> buffer) {
        if (buffer == preval) {
            std::cout << "The word \"" << buffer << "\" occured twice !\n";
            break;
        }
        preval = buffer;
    }
    if (preval != buffer) std::cout << "No repeated word\n";
}
