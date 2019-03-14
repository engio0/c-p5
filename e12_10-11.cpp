// #Exercise 12.10: Explain whether the following call to the process function
// defined on page 464 is correct. If not, how would you correct the call?include <iostream>
//
//     shared_ptr<int> p(new int(42));
//     process(shared_ptr<int>(p));
//
// Exercise 12.11: What would happen if we called process as follows?
//
//     process(shared_ptr<int>(p.get()));

#include <iostream>
#include <memory>

void process(std::shared_ptr<int> ptr)
{
    std::cout << "inside the process function: " << ptr.use_count() << '\n';
}

int main()
{
    std::shared_ptr<int> p(new int(42));
    process(std::shared_ptr<int>(p));

    /**
    * codes below shows how the reference count change.
    */
    std::cout << p.use_count() << "\n";
    auto q = p;
    std::cout << p.use_count() << "\n";
    std::cout << "the int p now points to is:" << *p << "\n";

    /** E12_11 **/
    process(std::shared_ptr<int>(p.get()));
    std::cout << p.use_count() << "\n";
    std::cout << "the int p now points to is:" << *p << "\n";

    return 0;
}
