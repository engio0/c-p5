// CHAPTER 12.1 DYNAMIC MEMORY AND SMART POINTERS
// p570

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class StrBlob {
    public:
        typedef std::vector<std::string>::size_type vs_size_type;
        StrBlob();
        StrBlob(std::initializer_list<std::string> il);
        vs_size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }
        void push_back(const std::string &t) { data->push_back(t); }
        void pop_back();
        std::string &front();
        const std::string &front() const;
        std::string &back();
        const std::string &back() const;
    private:
        std::shared_ptr<std::vector<std::string>> data;
        void check(vs_size_type i, const std::string &msg) const;
};

StrBlob::StrBlob(): data(std::shared_ptr<std::vector<std::string>>()) { }

StrBlob::StrBlob(std::initializer_list<std::string> il):
    data(std::make_shared<std::vector<std::string>>(il)) { }

void StrBlob::check(vs_size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

int main()
{
    // Exercise 12.1: How many elements do b1 and b2 have at the end of this
    // code?
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        std::cout << "before after inside b1 size : " << b1.size() << std::endl;
        std::cout << "before after inside b2 size : " << b2.size() << std::endl;
        b2.push_back("about");

        std::cout << "after inside b1 size : " << b1.size() << std::endl;
        std::cout << "after inside b2 size : " << b2.size() << std::endl;
    }
    std::cout << "outside b1 size : " << b1.size() << std::endl;

    const StrBlob b3{"hello", "world", "const"};
    std::cout << b3.front() << ", " << b3.back() << std::endl;
}
