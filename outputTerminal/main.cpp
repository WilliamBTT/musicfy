#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <mutex>

#include "datareader.h"

// Mutex for protecting global variable.
std::mutex mutexGlobal;
// global execution.
bool runningLoop = true;

void runCanBusReceiver(bool &runningCanBus)
{
    DataReader dataReader;
    dataReader.configureCanBus();
    dataReader.readingCanBusLoop(runningCanBus);
    while(runningCanBus){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Exiting can bus thread " << std::endl;
    mutexGlobal.lock();
    runningLoop = false;
    mutexGlobal.unlock();
}

int main()
{
    std::cout << "Output console running..." << std::endl;
    bool runningCanBus = true; // can bus execution.
    std::thread canbusThread(runCanBusReceiver, std::ref(runningCanBus));
    while (runningLoop)
    {
        mutexGlobal.unlock();
        // Setting time to sleep loop.
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        mutexGlobal.lock();
    }

    return 0;
}
