#include <iostream>
#include <string>
#include <vector>

int main()
{
    {
        int *pi = new int;
        std::string *ps = new std::string;
        std::cout << "int *pi = new int;\npi : " << pi << "\n*pi : " << *pi << std::endl;
        std::cout << "string *ps = new string;\nps : " << ps << "\n*ps : " << *ps << std::endl;
    }
    std::cout << std::string(40, '=') << std::endl;
    {
        int *pi = new int(1024);
        std::string *ps = new std::string(10, '9');
        std::cout << "int *pi = new int;\npi : " << pi << "\n*pi : " << *pi << std::endl;
        std::cout << "string *ps = new string;\nps : " << ps << "\n*ps : " << *ps << std::endl;
    }
}
