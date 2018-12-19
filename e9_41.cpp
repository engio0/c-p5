#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<char> vc{'H', 'e', 'l', 'l', 'o', '!'};
    std::string greet(vc.cbegin(), vc.cend());
    std::cout << greet << std::endl;
}
