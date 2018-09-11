#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s3 = "hiya";
    string s4("value");
    string s5 = "value";

    cout << "sizeof(string s3 = \"hiya\") = " << sizeof(s3) << endl;
    cout << "sizeof(string s4(\"value\") = " << sizeof(s4) << endl;
    cout << "sizeof(string s5 = \"value\") = " << sizeof(s5) << endl;
}
