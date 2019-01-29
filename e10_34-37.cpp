// Exercise 10.34: Use reverse_iterators to print a vector in reverse
// order.

// Exercise 10.35: Now print the elements in reverse order using ordinary
// iterators.

// Exercise 10.36: Use find to find the last element in a list of ints with
// value 0.

// Exercise 10.37: Given a vector that has ten elements, copy the elements
// from positions 3 through 7 in reverse order to a list.

#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>
#include <iterator>

int main()
{
    std::istringstream iss{"3 1 4 1 5 9 2"};
    std::vector<int> ivec;
    int ibuf;

    while (iss >> ibuf) {
        ivec.push_back(ibuf);
    }

    /******************** E10.34 ********************/
    for (auto i = ivec.crbegin(); i != ivec.crend(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    /******************** E10.35 ********************/ 
    for (auto i = ivec.cend(); i != ivec.cbegin();) {
        std::cout << *--i << " ";
    }
    std::cout << std::endl;

    /************************************************/

    iss.clear();
    iss.str(std::string("1 6 1 8 0 3 3 9 8 8 7 4 9 8 9 4 8 4 8 2 0 4 5 8 6 8"));
    std::list<int> ilist;

    while (iss >> ibuf) {
        ilist.push_back(ibuf);
    }
    for (auto i = ilist.cbegin(); i != ilist.cend(); ++i) {
        std::cout << *i << " ";
    }
    
    /******************** E10.36 ********************/ 
    auto it = find(ilist.crbegin(), ilist.crend(), 0);
    std::cout << "\nfound : " << *it << std::endl;
//    std::cout << "reverse iterator next : " << *(it+1) << std::endl;
    std::cout << "distance from the crend : " << distance(it, ilist.crend()) << std::endl;
    std::cout << "distance from the crbegin : " << distance(ilist.crbegin(), it) << std::endl;
    std::cout << "distance from crbegin to crend : " << distance(ilist.crbegin(), ilist.crend()) << std::endl;
    std::cout << "distance from crend to crbegin : " << distance(ilist.crend(), ilist.crbegin()) << std::endl;

    /******************** E10.37 ********************/ 
    ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ilist.clear();
    ilist.resize(5);
    copy(ivec.cbegin() + 2, ivec.cbegin() + 7, ilist.rbegin());
    for (auto i:ilist) std::cout << i << " ";
    std::cout << std::endl;
}
