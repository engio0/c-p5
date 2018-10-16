#include <string>
#include <vector>

double calc(double);
int count(const std::string &, char);
int sum(std::vector<int>::iterator, std::vector<int>::iterator, int);
std::vector<int> vec(10);

int main()
{
    count("abcda", 'a');
    calc(66);
    sum(vec.begin(), vec.end(), 3.9);
}
