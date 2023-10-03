#include <iostream>
#include <mutex>

using namespace std;

mutex g_mutex;  // protects g_i


void funcA() {
    cout << "funcA: start" << endl;
    const lock_guard<std::mutex> lock(g_mutex);
    cout << "funcA: ended" << endl;
}

void funcB() {
    cout << "funcB: start" << endl;
    const lock_guard<std::mutex> lock(g_mutex);
    funcB();
    cout << "funcB: ended" << endl;
}

int main() {
    funcB();
    return 0;
}