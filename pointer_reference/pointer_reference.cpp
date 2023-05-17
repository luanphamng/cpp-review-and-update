#include <iostream>

using namespace std;

struct Receiver_msg_t {
    uint8_t data;
    uint32_t dataLength;
};

struct Receiver_msg3_t {
    uint8_t data;
    uint32_t dataLength;
};

void functiontest(Receiver_msg_t &msg) {
    // Receiver_msg2_t msg2 = reinterpret_cast<Receiver_msg2_t>(msg);
    cout << "functiontest: " << (int)msg.data << endl;
}

void functiontest2(Receiver_msg_t* msg) {
    cout << "functiontest: " << (int)msg->data << endl;
}

int main() {
    Receiver_msg_t* msg = new Receiver_msg_t();
    msg->data = 100;
    msg->dataLength = 1;

    functiontest(*msg);
    printf("*msg: %p\n", *msg);
    printf("msg: %p\n", msg);
    functiontest(*msg);
    Receiver_msg_t msg2;
    printf("&msg2: %p\n", &msg2);
    msg2.data = 101;
    msg2.dataLength = 2;
    functiontest2(&msg2);

    Receiver_msg3_t* msg3 = reinterpret_cast<Receiver_msg3_t*>(msg);
    cout << (int)msg3->data << endl;
    return EXIT_SUCCESS;
}