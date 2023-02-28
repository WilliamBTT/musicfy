#include "messagedecoder.h"
#include <sstream>
#include <bitset>

MessageDecoder::MessageDecoder(std::vector<unsigned char> canFrameData)
    : _dataInputVector(canFrameData)
{
    // Initializing attributes.
    _notesStringMap = {
        {1, "DO"},
        {2, "RE"},
        {3, "MI"},
        {4, "FA"},
        {5, "SOL"},
        {6, "LA"},
        {7, "SI"},
        {0, "ERROR"}};
}

std::string MessageDecoder::decode()
{
    // Getting string of data frame CAN BUS.
    std::string numberHex = gettingHexString();


    return _messageReceived;
}

std::string MessageDecoder::gettingHexString()
{
    // Hexadecimal numbers start with "0x".
    std::string fullNumberHex = "0x";
    for (int i=0; i<=7; ++i)
    {
        std::stringstream ss;
        // The steps are: 1) char -> int.   2) int -> hex (string).
        ss << std::hex << static_cast<int>(_dataInputVector[i]);
        fullNumberHex = fullNumberHex + ss.str();
    }
    return fullNumberHex;
}

