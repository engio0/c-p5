#include <iostream>

int main()
{
    int ia[3][4] = { {0, 1, 2, 3},
                     {4, 5, 6, 7},
                     {8, 9, 10, 11} };
    int arr[10][20][30] = {0};
    int ix[3][4] = {0, 3, 6, 9};

    ia[2][3] = arr[0][0][0];
    int (&row)[4] = ia[1];
}
