#include <iostream>
#include <string>

int main()
{
    std::string s("some string");
    if (!s.empty())
        s[0] = toupper(s[0]);
    std::cout << s << std::endl;

    for (decltype(s.size()) i = 0; i < s.size() && !isspace(s[i]); ++i)
        s[i] = toupper( s[i] );
    std::cout << s << std::endl;

    return 0;
}
