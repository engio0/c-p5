#include <iostream>
#include <string>

int main(int, char**)
{
    std::cout << "Enter the NUMBER of strings : ";
    int num = 0;
    std::cin >> num;
    std::string* const p = new std::string[num];
    std::string buf;
    std::string* q = p;
    std::cout << "Enter strings...\n";
    while (std::cin >> buf && q != p + num)
        *q++ = buf;
    const size_t size = q - p;
    std::cout << "size = q - p = " << size << std::endl;

    for (size_t i = 0; i < size; ++i) {
        std::cout << i << ": " << p[i] << std::endl;
    }
    delete[] p;
    return 0;
}
