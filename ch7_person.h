// Exercise 7.4: Write a class named Person that represents the name and
// address of a person. Use a string to hold each of these elements.
// Subsequent exercises will incrementally add features to this class.

#ifndef CP_E7_04_h
#define CP_E7_04_h

#include <iostream>
#include <string>

class Person {
    private:
        std::string name;
        std::string address;
    public:
        auto get_name() const -> std::string const& { return name; }
        const std::string& get_address() const { return address; }
};

std::istream &read(std::istream &is, Person &item);
std::ostream &print(std::ostream &os, Person const &item);

#endif
