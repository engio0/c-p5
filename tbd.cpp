#include <iostream>

int main()
{
    double dval = 3.14;
    const double pi = 3.14;
    const double *cptr = &pi;
    cptr = &dval;
}
