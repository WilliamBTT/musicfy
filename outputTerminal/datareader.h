#ifndef DATAREADER_H
#define DATAREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

class DataReader
{
public:
    /**
     * @brief DataReader constructor.
     */
    DataReader();

    /**
     * @brief DataReader default constructor.
     */
    ~DataReader();

    /**
     * @brief configureCanBus. Configure can bus parameters.
     * @return "0" if it worked, "-1" if it failed.
     */
    int configureCanBus();

    /**
     * @brief configureData. Creating the socket CAN BUS configuration.
     * @return "-1" if failed. "0" if it worked.
     */
    int configureData();

    /**
     * @brief bindingSocketCan. Socket CAN BUS need a bind with address specification.
     * @return "0" if it worked. "-2" if it failed.
     */
    int bindingSocketCan();

    /**
     * @brief readCanBus. Read message in CAN BUS.
     * @return "0" if it worked. "-2" if it failed.
     */
    int readCanBus();

    /**
     * @brief readingCanBusLoop. Loop that call "readCanBus".
     * @return runCanBus. Condition to break the loop.
     */
    void readingCanBusLoop(bool &runCanBus);

private:
    /**
     * @brief _conectionResult, result of the connection to CAN BUS.
     */
    int _connectionInformation;

    /**
     * @brief _nbytes. Size of message that has been written.
     */
    int _nbytes;
    /**
     * @brief _addr. Protocol specific address information.
     */
    struct sockaddr_can _addr;

    /**
     * @brief _frame. Struct with data info to send the message (Id and data).
     */
    struct can_frame _frame;

    /**
     * @brief _ifr. Requirements of CAN BUS interface.
     */
    struct ifreq _ifr;

    /**
     * @brief _ifname. Interfaz name. It is constant. The interface used in this class is "vcan0",
     * that is the virtual interface.
     */
    const char *_ifname;
};

#endif // DATAREADER_H
