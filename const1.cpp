int main()
{
    int i = 0;
    int *const p1 = &i;
    const int ci = 42;
    const int *p2 = &ci;
    const int *const p3 = p2;
    const int &r = ci;

    i = ci;
    p2 = p3;
}
