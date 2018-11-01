// Exercise 7.4: Write a class named Person that represents the name and
// address of a person. Use a string to hold each of these elements.
// Subsequent exercises will incrementally add features to this class.

#ifndef CP_E7_04_h
#define CP_E7_04_h

#include <iostream>
#include <string>

class Person {
    friend std::istream &read(std::istream &is, Person &item);
    friend std::ostream &print(std::ostream &os, Person const &item);

    public:
        Person() = default;
        Person(std::string n) : name{n} {}
        Person(std::string n, std::string a) : name{n}, address{a} {}
        Person(std::istream &is) { read(is, *this); }
        auto getName() const -> std::string const& { return name; }
        const std::string& getAddress() const { return address; }

    private:
        std::string name;
        std::string address;
};

std::istream &read(std::istream &is, Person &item);
std::ostream &print(std::ostream &os, Person const &item);

#endif
