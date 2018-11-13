#include <iostream>
#include <string>

class Sales_data {
    public:
        Sales_data() = default;
        Sales_data(const std::string &s, unsigned n, double p) :
            bookNo(s), units_sold(n), revenue(p*n) {}
        explicit Sales_data(const std::string &s) : bookNo(s) {}
//        Sales_data(std::istream &is) : Sales_data() { read(is, *this); }
        std::string const& isbn() const { return bookNo; }
        Sales_data& combine(const Sales_data&);
    private:
        double avg_price() const { return units_sold ? revenue/units_sold : 0; }
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};

int main()
{
    std::string null_isbn("9-999-99999-9");
    Sales_data item1(null_isbn);
    Sales_data item2("9-999-99999-9");
}
