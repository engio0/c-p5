/*
 * Exercises Section 7.1.1
 * Exercise 7.1: Write a version of the transaction-processing program from §
 * 1.6 (p. 24) using the Sales_data class you defined for the exercises in §
 * 2.6.1 (p. 72).
 */

#include <iostream>
#include <string>


// "Sales_item.h"
struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

int main()
{
    Sales_data total;

    if (std::cin >> total) {
        Sales_data trans;
        while (std::cin >> trans
