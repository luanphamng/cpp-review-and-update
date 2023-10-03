#include <iostream>
#include <memory>
using namespace std;

class CallbackClass {

public:
    int mCallbackMember1;

public:
    CallbackClass() {
        std::cout << "CallbackClass Constructor called!" << std::endl;
    }

    ~CallbackClass() {
        std::cout << "CallbackClass Destructor called!" << std::endl;
    }

    void someFunction() {
        std::cout << "CallbackClass Some function called!" << std::endl;

    }
};

class HostClass {

public:
    std::unique_ptr<CallbackClass> ptr1 = std::make_unique<CallbackClass>();
    std::unique_ptr<CallbackClass> ptr2 = nullptr;

public:
    HostClass() {
        std::cout << "Host Constructor called!" << std::endl;
    }

    ~HostClass() {
        std::cout << "Host Destructor called!" << std::endl;
    }

    void registerListener() {
        if (ptr1 != nullptr) {
            std::cout << "Host::registerListener ptr1 is not nullptr" << std::endl;
            printf("HostClass::registerListener - ptr1 address %p\n", &ptr1);
        }
        // Move ownership of ptr1 to ptr2
        ptr2 = std::move(ptr1);

        if (ptr1 == nullptr) {
            std::cout << "Host::registerListener ptr1 is nullptr" << std::endl;
            printf("HostClass::registerListener - ptr1 address %p\n", &ptr1);
        }

        if (ptr2 != nullptr) {
            std::cout << "Host::registerListener ptr2 is not nullptr" << std::endl;
            printf("HostClass::registerListener - ptr2 address %p\n", &ptr2);
        }
    }

    void run() {
        cout << "HostClass::run - Trying to access ptr2 from func2" << endl;
        ptr2->someFunction();
        printf("HostClass::run - ptr2 address %p\n", &ptr2);
    }
};



int main() {
    HostClass *host = new HostClass();
    host->registerListener();
    host->run();
    cout << "main() - going to ended" << endl;
    return 0;
}
