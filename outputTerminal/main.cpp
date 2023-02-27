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


int main()
{
    // Registering "SIGINT" signal to the handler function "signalHandler".
    signal(SIGINT, signalHandler);

    bool running = true;
    while (running)
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
            //
        }
        else if (mode ==1)
        {
            // Code to stop CAN BUS if it was active.
            // CRUD.
            std::cout << "doing some CRUD" << std::endl;
        }
        mutexMode.unlock();
    }

    return 0;
}
