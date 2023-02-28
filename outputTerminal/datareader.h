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

    /**
     * @brief checkingEndingMessage, check if input message has ID 0x333. In that case,
     * the program must be stopped.
     * @return bool if program must be stopped.
     */
    bool checkingEndingMessage();

    /**
     * @brief setMelodiesVector, setting _melodiesVector attribute.
     * @param melodiesVector, value to set _melodiesVector attribute.
     */
    void setMelodiesVector(std::vector<std::pair<std::string, std::string>> melodiesVector);

    /**
     * @brief lookForPossibleMatch, checking if the input message decoded is in any song of database.
     */
    void lookForPossibleMatch();

private:
    /**
     * @brief _messageDecoder, instance of MessageDecoder.
     */
    MessageDecoder _messageDecoder;

    /**
     * @brief _frameCanBus, copy of Can Bus data frame.
     */
    std::vector <unsigned char> _frameCanBus;

    /**
     * @brief _messageDecoded message decoded from CAN BUS.
     */
    std::string _messageDecoded;

    /**
     * @brief _melodiesVector, read from data base
     */
    std::vector<std::pair<std::string, std::string>> _melodiesVector;
};

#endif // DATAREADER_H
