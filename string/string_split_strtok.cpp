// Example program
#include <iostream>
#include <string>
#include <cstring> // strtok

using namespace std;


int a[10];
int main()
{
    std::string str("123,456,789,0");

    char *cstr = new char[str.length() + 1];
    std::strcpy(cstr, str.c_str());

    // cstr now contains a c-string copy of str

    char *ptr = std::strtok(cstr, ",");
    int id = 0;
    
    while (ptr != nullptr)
    {
        string msgId = ptr;
        a[id] = stoi(msgId);
        id++;

        ptr = strtok(NULL, ",");
    }
    
    cout << a[0] << ", " << a[1] << ", " << a[2] << endl;
}
