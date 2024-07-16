#include <iostream>
#include <string.h>
#include <stdio.h>


#define LCF_FOLDER_PATH "/opt/config/lcf"

#define FILE_NAME_LONG "lge.framework.vehicle.drv4x4iservice.dimension_L6635DRAirlge.framework.vehicle.drv4x4iservice.dimension_L6635DRAirlge.framework.vehicle.drv4x4iservice.dimension_L6635DRAir"

#define FILE_NAME_SHORT "lge.framework.vehicle.drv4x4iservice.dimension_L6635DRAir"

int main() {
    char fileName[100];
    snprintf(fileName, sizeof(fileName), "%s/%s.json", LCF_FOLDER_PATH, FILE_NAME_SHORT);
    std::cout << "snprintf FILE_NAME_SHORT: " << fileName << std::endl;
    std::cout << "snprintf FILE_NAME_LONG: " << strlen(fileName) << std::endl;

    snprintf(fileName, sizeof(fileName), "%s/%s.json", LCF_FOLDER_PATH, FILE_NAME_LONG);
    std::cout << "snprintf FILE_NAME_LONG: " << fileName << std::endl;
    std::cout << "snprintf FILE_NAME_LONG: " << strlen(fileName) << std::endl;

    
    return EXIT_SUCCESS;
}
