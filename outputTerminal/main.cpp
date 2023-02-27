#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <mutex>

#include "datareader.h"

// Mutex for protecting global variable.
std::mutex mutexMode;
// Global variable. Mode = 0 -> CAN BUS listening. Mode = 1 -> CRUD.
int mode;

// Handler linked to SIGINT signal (control + C ).
void signalHandler(int signum) {
    // Update value of global variable, protected with mutex.
    mutexMode.lock();
    ++mode;
    if (mode > 1)
    {
        mode = 0;
    }
    std::cout << "Mode ... " << mode <<std::endl;
    mutexMode.unlock();
}

void runCanBusReceiver(bool &runningCanBus)
{
    DataReader dataReader;
    dataReader.configureCanBus();
    dataReader.readingCanBusLoop(runningCanBus);
    while(runningCanBus){
        std::cout << "Can Bus Running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Exiting can bus thread " << std::endl;
}

int main()
{
    // Registering "SIGINT" signal to the handler function "signalHandler".
    signal(SIGINT, signalHandler);

    // Variable for controlling execution flow.
    bool runningLoop = true; // global execution.
    bool runningCanBus = true; // can bus execution.
    bool runningCRUD = false; // CRUD execution.
    std::thread canbusThread(runCanBusReceiver, std::ref(runningCanBus));
    while (runningLoop)
    {
        // Setting time to sleep loop.
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // Protect global variable with Mutex.
        mutexMode.lock();
        if(mode ==0){
            // Can Bus listening.
            std::cout << "Can Bus listening" << std::endl;

        }
        else if (mode ==1)
        {
            // CRUD.
            std::cout << "doing some CRUD" << std::endl;
        }
        mutexMode.unlock();
    }

    return 0;
}
