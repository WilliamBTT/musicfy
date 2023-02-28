#include "datareader.h"
#include <string>

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
        _messageDecoder.setMelodiesVector(_melodiesVector);
        _messageDecoded = _messageDecoder.decode(_frameCanBus);
        std::cout << "Message received is " << _messageDecoded << std::endl;
        lookForPossibleMatch();


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

void DataReader::setMelodiesVector(std::vector<std::pair<std::string, std::string> > melodiesVector)
{
    _melodiesVector = melodiesVector;
}

void DataReader::lookForPossibleMatch()
{
    bool match = false;
    for (int i=0; i<_melodiesVector.size(); ++i)
    {
        size_t found = _melodiesVector[i].second.find(_messageDecoded);
        if (found != std::string::npos) {
            match = true;
            size_t lenMelody = _messageDecoded.length();
            size_t lenMelodyDataBase = _melodiesVector[i].second.length();
            int percentageMatch = lenMelody * 100 / lenMelodyDataBase;
            std::cout << "Match at song '" << _melodiesVector[i].first << "' with a percentage of "
                      << percentageMatch << "%"<< std::endl;
        }
    }
    if (!match)
    {
        std::cout << "No match for this melody" << std::endl;
    }
}
