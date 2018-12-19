// Exercise 9.46: Rewrite the previous exercise using a position and length to
// manage the strings. This time use only the insert function.
//
// Exercise 9.45: Write a funtion that takes a string representing a name
// and two other strings representing a prefix, such as “Mr.” or “Ms.” and a
// suffix, such as “Jr.” or “III”. Using iterators and the insert and append
// functions, generate and return a new string with the suffix and prefix
// added to the given name.

#include <iostream>
#include <string>

std::string &add_pre_suf(std::string &name, const std::string &prefix, const std::string &suffix)
{
    name.insert(name.cbegin(), prefix.cbegin(), prefix.cend());
    return name.append(suffix);
}

int main()
{
    std::string name = "Charlie";
    std::string prefix = "Mr.";
    std::string suffix = "Jr.";

    add_pre_suf(name, prefix, suffix);
    std::cout << name;
}
