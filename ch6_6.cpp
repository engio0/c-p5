void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);

void test()
{
    f(42, 2.56);
}
