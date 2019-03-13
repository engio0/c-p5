#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <vector>

int main()
{
// p.563
    std::shared_ptr<std::string> p1;
    std::shared_ptr<std::list<int>> p2;

    if (p1 && p1->empty()) {
        *p1 = "hi";
        std::cout << "*p1 = " << *p1 << std::endl;
    }
    std::cout << "p2 = " << p2 << std::endl;

// p.564
    std::shared_ptr<int> p3 = std::make_shared<int>(42);
    std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
    
    std::cout << "p3 = " << p3 << ", *p3 = " << *p3 << ", p3.get = " << p3.get() << std::endl;

// p.565
    std::shared_ptr<int> p5 = std::make_shared<int>();
    auto p6 = std::make_shared<std::vector<std::string>>();
    std::cout << "p5 = " << p5 << ", *p5 = " << *p5 << std::endl;
    std::cout << "p6 = " << p6 << ", *p6->capacity() = " << p6->capacity()
              << ", p6->size() = " << p6->size() << std::endl;
    std::cout << "push_backing on p6... \n";
    p6->push_back("push backing...");
    std::cout << "p6 = " << p6 << ", *p6->capacity() = " << p6->capacity()
              << ", p6->size() = " << p6->size() << std::endl;
}
