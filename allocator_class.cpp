#include <iostream>
#include <memory>
#include <string>

void p602()
{
    std::cout << "========== p602 ==========\n";

    size_t num = 0;
    std::cout << "Enter allocation size : ";
    std::cin >> num;

    std::allocator<std::string> stralloc;
    auto const p = stralloc.allocate(num);
    std::cout << "p : " << p << std::endl;

    auto q = p;
    stralloc.construct(q++);
    stralloc.construct(q++, 10, 'c');
    stralloc.construct(q++, "hi");

    //std::cout << "Constructed " << stralloc.max_size() << std::endl;

    std::string buf;
    for (size_t i = 0; i < num; ++i) {
        std::cout << p+i << " : " << p[i] << std::endl;
    }

    while (q != p) {
        stralloc.destroy(--q);
    }

    stralloc.deallocate(p, num);
}

void p604()
{
    std::cout << "========== p604 ==========\n";
}

class StrVec {
    std::string* elements;
    std::string* first_free;
    std::string* cap;
    std::allocator<std::string> alloc;
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();
    void push_back(const std::string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string* begin() const { return elements; }
    std::string* end() const { return first_free; };
private:
    void reallocate();
    void free();
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
};

void StrVec::push_back(const std::string& str)
{
    chk_n_alloc();
    alloc.construct(first_free++, str);
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements) {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec& s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec& StrVec::operator=(const StrVec& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

int main()
{
    p602();
    p604();
}
