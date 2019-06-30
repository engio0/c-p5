#include <cstdio>
#include <cstdlib>

int main(int, char** argv)
{
    int option = std::atoi(argv[1]);
    switch (option) {
        case 1:
            std::puts("It was one");
            for (option = 1; option <= 10; ++option) {
        default:
            std::printf("It was %d\n", option);
            }
    }
}
