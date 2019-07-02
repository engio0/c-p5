#include <cstdio>

int main()
{
    for (int i = -3; i <= 3; ++i) {
        printf("%2d : %s\n", i, ( i ? "true" : "false" ));
    }
    return 0;
}
