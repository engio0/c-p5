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

int main()
{
    std::istringstream iss{"3 1 4 1 5 9 2"};
    std::vector<int> ivec;
    std::list<int> ilist;
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

    /************************************************/

    iss.str("1 6 1 8 0 3 3 9 8 8 7");
    while (iss >> ibuf) {
        ilist.push_back(ibuf);
    }
    
    /******************** E10.36 ********************/ 
}
