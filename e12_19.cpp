// Exercise 12.19: Define your own version of StrBlobPtr and update your
// StrBlob class with the appropriate friend declaration and begin and end
// members.

#include <iostream>
#include <memory>
#include <vector>


class StrBlobPtr {
    public:
        StrBlobPtr(): curr(0) { }
        StrBlobPtr(StrBlobPtr &a, size_t sz = 0):
            wptr(a.data), curr(sz) { }
        std::string& deref() const;
        StrBlobPtr& incr();

    private:
        std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
        std::weak_ptr<std::vector<std::string>> wptr;
        std::size_t curr;
};
