#include <iostream>
using namespace std;

int main()
{
    int a = 3, b = 4;
    decltype(a) c = a;
    decltype(a = b) d = a;
    
    cout << "a = " << a << ", b = " << b << endl;
    cout << "c = " << c << ", d = " << d << endl;
}
