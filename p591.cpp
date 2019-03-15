#include <iostream>
#include <memory>
#include <string>

int main()
{
    auto p = std::make_shared<int>(42);
    std::weak_ptr<int> wp(p);
    std::cout << p.use_count() << ", " << wp.use_count() << '\n';

    if (std::shared_ptr<int> np = wp.lock()) {
        std::cout << *np << '\n';
    }
}
