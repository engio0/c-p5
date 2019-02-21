#include <iostream>
#include <vector>
#include <set>

int main()
{
    // define a vector with 20 elements, holding two copies of each number from 0 to 9std::vector<int> ivec;
    std::vector<int> ivec;
    for (std::vector<int>::size_type i = 0; i <10; ++i) {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    // iset holds unique elements from ivec; miset holds all 20 elements
    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> miset(ivec.cbegin(), ivec.cend());
    std::cout << "ivec.size :" << ivec.size() << std::endl;
    std::cout << "iset.size :" << iset.size() << std::endl;
    std::cout << "miset.size :" << miset.size() << std::endl;
}
