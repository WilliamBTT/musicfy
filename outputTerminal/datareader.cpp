#include "datareader.h"

DataReader::DataReader()
{
    _ifname = "vcan0";
//    configureCanBus();
}

DataReader::~DataReader()
{
    // Nothing to do.
}

int DataReader::readCanBus()
{
    // Reading canBus Message.
    _nbytes = read(_connectionInformation, &_frame, sizeof(struct can_frame));

    if (_nbytes < 0) {
        perror("Error al leer el socket CAN");
        return 1;
    }

    return 0;
}

void DataReader::readingCanBusLoop(bool &runCanBus)
{
    while(runCanBus)
    {
        // Reading can bus.
        readCanBus();

        // Checking if input message is ending message.
        if (checkingEndingMessage())
        {
            runCanBus = false;
            break;
        }

        // Filling can bus frame to get the string.
        fillingFrameCanBus();

        // Getting string (same message as in input terminal).
        _messageDecoded = _messageDecoder.decode(_frameCanBus);
        std::cout << _messageDecoded << std::endl;
        int a = 1;
    }
}

void DataReader::fillingFrameCanBus()
{
    _frameCanBus.clear();
    for (int i=0; i<=7; ++i)
    {
        _frameCanBus.push_back(_frame.data[i]);
    }
}

bool DataReader::checkingEndingMessage()
{
    if (_frame.can_id ==  0x333)
    {
        return true;
    }
    return false;
}
