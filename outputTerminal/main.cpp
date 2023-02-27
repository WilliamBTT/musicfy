#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <mutex>

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
    bool runningCanBus = false; // can bus execution.
    bool runningCRUD = false; // CRUD execution.
    std::thread canbusThread;
    while (runningLoop)
    {
        // Setting time to sleep loop.
        std::chrono::milliseconds timeout(2000);
        std::this_thread::sleep_for(timeout);

        // Protect global variable with Mutex.
        mutexMode.lock();
        if(mode ==0){
            // Code to stop CRUD if it was active.
            // Can Bus listening.
            std::cout << "Can Bus listening" << std::endl;
            if (!runningCanBus){
                runningCanBus = true;
                canbusThread = std::thread(runCanBusReceiver, std::ref(runningCanBus));
            }

        }
        else if (mode ==1)
        {
            // Code to stop CAN BUS if it was active.
            if (runningCanBus){
                runningCanBus = false;
                if (canbusThread.joinable())
                {
                    canbusThread.join();  // If canbus thread is active, wait until it stops.
                }
            }

            // CRUD.
            std::cout << "doing some CRUD" << std::endl;
        }
        mutexMode.unlock();
    }

    return 0;
}
