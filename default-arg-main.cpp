#include <iostream>

class Test {public: int testing(int input=42);};
int f();
int main()
{
    Test t;
    std::cout << t.testing()
              << " " << f()
              << std::endl;
    return 0;
}
