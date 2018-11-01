#include <iostream>
#include "ch7_person.h"

std::istream &read(std::istream &is, Person &item)
{
    is >> item.name >> item.address;
    return is;
}

std::ostream &print(std::ostream &os, Person const &item)
{
    return os << item.name << " " << item.address;
}

