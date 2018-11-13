#include <iostream>
#include <string>

class Account {
    public:
        void calculate() { amount += amount * interestRate; }
        static double rate() { return interestRate; }
        static void rate(double r) { interestRate = r; }
    private:
        std::string owner;
        double amount;
        static double interestRate;
        static double initRate();
};
