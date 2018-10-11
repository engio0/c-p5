#include <stdio.h>

int main()
{
    int c;
    puts("Enter text. Include dot('.') in a sentence to exit:");
    do{
        c=getchar();
        putchar(c);
    } while (c != '.');
    return 0;
}
