#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std::placeholders;


class MpdtManager {
    std::mutex m_Mutex;
    std::condition_variable mDownlinkCondition {};
    bool m_bDataLoaded;

    public:
    MpdtManager() {
        m_bDataLoaded = false;
    }

    void loadData() {
        std::this_thread::sleep_for(std::chrono::miliseconds(1000));
        std::cout << "Loading data from file" << std::endl;

        std::lock_guard<std::mutex> guard(m_Mutex);

        m_bDataLoaded = true;

        mDownlinkCondition.notify_all();
    }

    bool isDataLoaded() {
        return m_bDataLoaded;
    }

    void mainTask() {
        std::cout << "mainTask::Do some thing handsahing" << std::endl;

        std::unique_lock<std:mutex> mlock(m_Mutex);

        mDownlinkCondition.wait(mlock, std::bind(&MpdtManager::isDataLoaded, this));
        std::cout <<"Do Processing On Loaded Data" << std::endl;
    }

}
int main() {
    MpdtManager mdptMgr;
    std::thread thread_1(&MpdtManager::mainTask, &mdptMgr);
    std::thread thread_2(&MpdtManager::loadData, &mdptMgr);
    thread_2.join();
    thread_1.join();
    return EXIT_SUCCESS;
}