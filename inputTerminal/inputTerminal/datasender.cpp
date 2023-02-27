#include "datasender.h"

DataSender::DataSender()
    : _ifname("vcan0")
{

}

DataSender::~DataSender()
{

}

void DataSender::setMessageVectorInt(std::vector<int> messageVectorInt)
{
    _messageVectorInt = messageVectorInt;
}
