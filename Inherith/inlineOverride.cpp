#include <iostream>

using namespace std;

class Parent {
public:
    Parent() {
        cout << "Parent cstor" << endl;
    };

    virtual void overrideMe() {
        cout << "This is overrideMe in parent" << endl;
    };
};

class Child : public Parent {
public:
    virtual void overrideMe() {}
};

int main() {
    Parent *p = new Parent();
    p->overrideMe();

    Child *c = new Child();
    c->overrideMe();
    return 0;
}