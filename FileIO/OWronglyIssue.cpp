#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

#define ECALL_DATA_PATH "/home/luanpham/projects/cpp_review/apps/bcall"
#define LOGD printf
#define LOGV printf

void notExistECallDataPath()
{
    LOGD("notExistECallDataPath ++\n");
    int32_t fd = open(ECALL_DATA_PATH, O_WRONLY); // fixed Coverity Static Issue.
    if (fd >= NULL)
    {
        LOGD("%s open success\n", ECALL_DATA_PATH);
        close(fd);
    }
    else
    {
        std::string root_path = std::string(ECALL_DATA_PATH);
        if (mkdir(root_path.c_str(), 0755) < 0)
        {
            LOGV("can not create path:%s\n", root_path.c_str());
        }
        else
        {
            LOGD("%s folder is created\n", root_path.c_str());
        }
    }
}

void notExistECallDataPath2()
{
    LOGD("notExistECallDataPath ++\n");
    struct stat sb;
    if (stat(ECALL_DATA_PATH, &sb) == 0)
    {
        if (access(ECALL_DATA_PATH, W_OK) != 0 || access(ECALL_DATA_PATH, R_OK) != 0)
        {
            LOGV("the ECALL_DATA_PATH hasn't a read/writepermission. So, give a permission for this path.\n");
            chmod(ECALL_DATA_PATH, S_IRWXU);
        }
        else
        {
            LOGV("the ECALL_DATA_PATH has a read/write permission\n");
        }
    }
    else
    {
        std::string root_path = std::string(ECALL_DATA_PATH);
        if (mkdir(root_path.c_str(), 0755) < 0)
        {
            LOGV("can not create path:%s\n", root_path.c_str());
        }
        else
        {
            LOGD("%s folder is created\n", root_path.c_str());
        }
    }
}


int main()
{
    // cout << "notExistECallDataPath: ";
    // notExistECallDataPath();
    // cout << endl;

    cout << "notExistECallDataPath2: ";
    notExistECallDataPath2();
    cout << endl;
    cout << "Exited" << endl;
    return EXIT_SUCCESS;
}