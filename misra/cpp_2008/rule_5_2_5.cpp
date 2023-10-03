#include <iostream>
#include <stdio.h>

#define DEVICE_MDEL "avi2_full"

int main() {
    printf("%s : device=%s", __func__, (const char*)DEVICE_MDEL);
    return 0;
}