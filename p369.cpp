#include <iostream>
#include <string>

typedef double Money1;
std::string bal1;

class Account1 {
    public:
        Money1 balance() { return bal; }
    private:
        Money1 bal;
};

typedef double Money2;

class Account2 {
    public:
        Money2 balance() { return bal; }
        void printSize() { std::cout << sizeof(bal) << std::endl; }
    private:
        typedef char Money2;
        Money2 bal;
};

int main()
{
    Account2 item;
    item.printSize();
}
