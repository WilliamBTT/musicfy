#ifndef DATASENDER_H
#define DATASENDER_H

#include <vector>
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

class DataSender
{
public:
    /**
     * @brief DataSender constructor.
     */
    DataSender();

    /**
     * @brief DataSender default constructor.
     */
    ~DataSender();

    /**
     * @brief setMessageVectorInt. Setter of the message data input.
     * @param messageVectorInt. Vector with data. It will set
     * "_messageVectorInt" attribute.
     */
    void setMessageVectorInt(std::vector<int> messageVectorInt);

private:
    /**
     * @brief _messageVectorHex, Vector with data message in integer values.
     * These integer values will be used to fill messageData in this class.
     */
    std::vector<int> _messageVectorInt;

    /**
     * @brief _conectionResult, result of the connection to CAN BUS.
     */
    int _conectionResult;

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

#endif // DATASENDER_H
