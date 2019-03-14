#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> p(new int(42));
    std::cout << "shared_ptr p = " << p << ", *p = " << *p
              << ", with count " << p.use_count() << std::endl;
    std::shared_ptr<int> q(p);
    std::cout << "shared_ptr q = " << q << ", *q = " << *q
              << ", with count " << q.use_count() << std::endl;
    std::cout << "shared_ptr p = " << p << ", *p = " << *p
              << ", with count " << p.use_count() << std::endl;
    p.reset(new int(1024));
    std::cout << "shared_ptr q = " << q << ", *q = " << *q
              << ", with count " << q.use_count() << std::endl;
    std::cout << "shared_ptr p = " << p << ", *p = " << *p
              << ", with count " << p.use_count() << std::endl;

    if (!p.unique())
        p.reset(new int(666));
    *p += 333;
    std::cout << "shared_ptr p = " << p << ", *p = " << *p
              << ", with count " << p.use_count() << std::endl;
}
