#include <iostream>
#include <sys/wait.h>

#include <sys/types.h> /* Primitive System Data Types */
#include <errno.h> /* Errors */
#include <stdio.h> /* Input/Output */

using namespace std;

int main() {
    pid_t pid = fork();
    int32_t status;

    waitpid(pid, &status, 0);

    WIFEXITED(status);

    cout << status;
    return 0;
}