// The smart pointer constructors that take pointers are explicit (§ 7.5.4, p. 296).
// Hence, we cannot implicitly convert a built-in pointer to a smart pointer; we must use
// the direct form of initialization (§ 3.2.1, p. 84) to initialize a smart pointer:

#include <memory>

int main()
{
//    std::shared_ptr<int> p1 = new int(1024);
    std::shared_ptr<int> p2(new int(1024));
    std::shared_ptr<int> p3{new int(1024)};
}
