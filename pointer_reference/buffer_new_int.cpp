#include <iostream>

using namespace std;


void functionCheckIt(bool &data) {
    cout << "data = " << data << endl;
    uint8_t *p = new uint8_t(1);
    // printf("After getting data: %d", *p);
    cout << *p;
}

int main() {
    bool t = 9;
    functionCheckIt(t);
    return EXIT_SUCCESS;
}