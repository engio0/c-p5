#include <iostream>
#include <string>

/******************** declarations ********************/
class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    public:
        Sales_data(const std::string &str, unsigned num, double price)
            : bookNo(str), units_sold(num), revenue(num*price) {
                std::cout << "3 args constructor\n"; }
        Sales_data(const std::string& str) : Sales_data(str, 0, 0) {
                std::cout << "1 arg constructor\n"; }
        Sales_data() : Sales_data("") { std::cout << "no arg constructor\n"; }
        Sales_data(std::istream &is) : Sales_data() { read(is, *this); }
        std::string const& isbn() const { return bookNo; }
        Sales_data& combine(const Sales_data&);
    private:
        double avg_price() const { return units_sold ? revenue/units_sold : 0; }
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};


/******************** definitions ********************/
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

/******************** main ********************/
int main()
{
    Sales_data total;
    if (read(std::cin, total)) {
        Sales_data trans;
        while (read(std::cin, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(std::cout, total) << std::endl;
                total = trans;
            }
        }
        print(std::cout, total) << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}
