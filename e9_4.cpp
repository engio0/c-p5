#include <vector>

bool hasint(std::vector<int>::const_iterator i1, std::vector<int>::const_iterator i2, int val)
{
    for (; i1 != i2; ++i1) {
        if (*i1 == val) return true;
    }
    return false;
}
