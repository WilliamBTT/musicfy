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
#include "canbus.h"
#include "messagedecoder.h"

class DataReader : public CanBus
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
     * @brief readCanBus. Read message in CAN BUS.
     * @return "0" if it worked. "-2" if it failed.
     */
    int readCanBus();

    /**
     * @brief readingCanBusLoop. Loop that call "readCanBus".
     * @return runCanBus. Condition to break the loop.
     */
    void readingCanBusLoop(bool &runCanBus);

    /**
     * @brief fillingFrameCanBus, filling the can bus data frame copy.
     */
    void fillingFrameCanBus();

private:
    /**
     * @brief _messageDecoder, instance of MessageDecoder.
     */
    MessageDecoder _messageDecoder;

    /**
     * @brief _frameCanBus, copy of Can Bus data frame.
     */
    std::vector <unsigned char> _frameCanBus;

    std::string _messageDecoded;
};

#endif // DATAREADER_H
