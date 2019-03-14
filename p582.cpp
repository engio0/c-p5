#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> p(new int(42));
    int *q = p.get();

    std::cout << "shared_ptr p = " << p << ", *p = " << *p <<  std::endl;
    std::cout << "built-in ptr q = " << q << ", *q = " << *q << std::endl;

    {
        std::shared_ptr<int> pi(q);
        std::cout << "shared_ptr pi = " << pi << ", *pi = " << *pi <<  std::endl;
    }
    int foo = *p;
    std::cout << "shared_ptr p again = " << p << ", *p = " << *p <<  std::endl;
    std::cout << foo << std::endl;
}
