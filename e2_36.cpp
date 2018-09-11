#include <iostream>
using namespace std;

int main()
{
    int a = 3, b = 4;
    cout << "a = " << a << ", b = " << b << endl;
    decltype(a) c = a;
    decltype((b)) d = b;
    cout << "c = " << c << "\n++c" << endl;
    ++c;
    cout << "c = " << c << endl;
    cout << "d = " << d << "\n++d" << endl;
    ++d;
    cout << "d = " << d << endl;
    cout << "a = " << a << ", b = " << b << endl;
}
