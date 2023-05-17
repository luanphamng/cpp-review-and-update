#include <iostream>

#define cout2(str) std::cout << __func__ << ": " << str

int main() {
    cout2("aabd %d", 14);
    return 1;
} 