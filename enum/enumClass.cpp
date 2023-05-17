#include <iostream>

using namespace std;

enum class Receiver_msg_ID {
    OBG_MSG,
    SOME_IP_MSG
};

int main() {
    cout << int(Receiver_msg_ID::OBG_MSG) << endl;
    cout << int(Receiver_msg_ID::SOME_IP_MSG);
    return EXIT_SUCCESS;
}