#include <iostream>

using namespace std;
class A {
    public:
    A() {}


    int x = 9;
public:
    void action() {
        printX();
    } 
    private:
    virtual void printX() {
        std::cout << "aa";
    }
};

class B : public A {

public:
    
    void actionB() {
        printX();
    } 

private:
    void printX() {
        std::cout << "B.printX" << endl;
    };
};

int main() {
    A *b ;
    b->action();
    return 0;
}