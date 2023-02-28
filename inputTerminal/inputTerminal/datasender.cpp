#include "datasender.h"
#include <iostream>
#include <cstring>

DataWriter::DataWriter()
{
    _ifname = "vcan0";
}

DataWriter::~DataWriter()
{
    // Nothing to do.
}

void DataWriter::setMessageVectorInt(std::vector<int> messageVectorInt)
{
    _messageVectorInt = messageVectorInt;
}

int DataWriter::sendMessage()
{
    // Filling data frame with data vector input.
    fillDataFrame();
    // Last step, writing in CAN BUS with data stored.
    writeCanBus();
    return 0;
}

void DataWriter::fillDataFrame()
{
    _frame.can_id = 0x222;
    _frame.can_dlc = 8;

    std::string hex_string = "DA"; // Representa el número hexadecimal 2A

  int decimal_num = std::stoi(hex_string, nullptr, 16);
    for (int i=0; i<=7; i++)
    {
        int data = _messageVectorInt[i];
        _frame.data[i] = _messageVectorInt[i];
    }

}

int DataWriter::writeCanBus()
{
    _nbytes = write(_connectionInformation, &_frame, sizeof(struct can_frame));
    return _nbytes;
}

void DataWriter::endingProgram()
{
    // Settinng special ID for ending program message.
    _frame.can_id = 0x333;
    _frame.can_dlc = 8;
    for (int i=0; i<=7; i++)
    {
        // Setting all bits to '1' for ending program message.
        _frame.data[i] = 255;
    }
    int size = writeCanBus();
}

