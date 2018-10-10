#include <iostream>
#include <vector>

bool is_prefix(std::vector<int> const &v1, std::vector<int> const &v2)
{
    if (v1.size() > v2.size()) {
        return is_prefix(v2, v1);
    }

    for (auto i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

int main()
{
    std::vector<int> v1{ 0, 1, 1, 2 };
    std::vector<int> v2{ 0, 1, 1, 2, 3, 5, 8 };

    std::cout << (is_prefix(v1, v2) ? "yes\n" : "no\n");

    v2 = {0, 1, 1, 3, 3, 5, 8};
    std::cout << (is_prefix(v1, v2) ? "yes\n" : "no\n");
    
    v1 = {0, 1, 2, 3, 4, 5};
    v2 = {0, 1, 2};
    std::cout << (is_prefix(v1, v2) ? "yes\n" : "no\n");
}
