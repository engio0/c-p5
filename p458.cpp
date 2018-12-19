#include <string>
#include <iostream>

int main()
{
    const char *cp = "Hello World!!!";
    char noNull[] = {'H', 'i'};
    std::string s1(cp);
    std::string s2(noNull, 2);
    std::cout << "sizeof s2 : " << sizeof(s2) << ", s2.size() : " << s2.size() << std::endl;
    std::string s3(noNull);
    std::cout << s3 << " : " << sizeof(s3) << ", " << s3.size() << std::endl;
    std::string s4(cp + 6, 5);
    std::string s5(s1, 6, 5);
    std::string s6(s1, 6);
    std::string s7(s1, 6, 20);
//    std::string s8(s1, 16);
}
