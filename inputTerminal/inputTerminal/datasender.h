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
#include <iostream>
#include "../../outputTerminal/canbus.h"

class DataSender : public CanBus
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

    /**
     * @brief sendMessage. Initializing data sending.
     * @return "-1" if failed. "0" if it works.
     */
    int sendMessage();

    /**
     * @brief fillDataFrame. Fill "_frame" attribute that contains data to send to CAN BUS.
     */
    void fillDataFrame();

    /**
     * @brief writeCanBus. Write message in CAN BUS.
     * @return size of message that has been written (_nbytes attribute).
     */
    int writeCanBus();

    /**
     * @brief endingProgram. It sends a message with all bits to '1' and a special Identifier (999).
     * It means that the user press ":q" and the program is ended.
     */
    void endingProgram();

private:
    /**
     * @brief _messageVectorHex, Vector with data message in integer values.
     * These integer values will be used to fill messageData in this class.
     */
    std::vector<int> _messageVectorInt;

};

#endif // DATASENDER_H
