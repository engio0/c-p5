#include <iostream>
#include <cstdio>

int main(int argc, char* argv)
{
    for (int i = 0; i < argc; ++i) {
        std::cout << ((char**)argv)[i] << std::endl;
        printf("%s\n", ((char**)argv)[i]);
    }
}
