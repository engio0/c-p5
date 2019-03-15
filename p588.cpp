#include <iostream>
#include <memory>
#include <string>

int main()
{
    std::unique_ptr<std::string> p1(new std::string("Stegosaurus"));
    std::cout << "p1 = " << p1.get() << ", *p1 = " << *p1 << '\n';

    std::cout << "Releasing p1...\n";
    auto av = p1.release();         // release DON'T FEE RESOURCE !!!
    std::cout << "p1 = " << p1.get() << /* ", *p1 = " << *p1 << */ '\n';
    std::cout << "av = " << av << ", *av = " << *av << '\n';
    
    std::cout << "Resetting p1 with av...\n";
    p1.reset(av);
    std::cout << "p1 = " << p1.get() << ", *p1 = " << *p1 << '\n';
    std::cout << "av = " << av << '\n';
}
