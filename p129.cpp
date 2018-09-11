#include <iostream>
#include <string>

using namespace std;

int main()
{
    string line;
    while (getline(cin, line))
        if (!line.empty()) {
            int strsize = line.size();
            cout << strsize << " : " << line << endl;
        }
    return 0;
}
