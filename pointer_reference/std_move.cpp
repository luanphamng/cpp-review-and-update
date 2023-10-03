#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {

    string foo = "foo-string";
    string bar = "bar-string";

    vector<string> mVectorStr;

    mVectorStr.push_back(foo);
    mVectorStr.push_back(std::move(bar));

    cout << "mVectorStr contains: ";

    for (std::string& str:mVectorStr)
        std::cout << ' ' << str;
    cout << endl;

    cout << foo << endl;

    cout << bar << endl; // bar mat data sau khi move

    return 0;
}