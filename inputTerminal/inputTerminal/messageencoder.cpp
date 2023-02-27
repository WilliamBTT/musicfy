#include "messageencoder.h"
#include <bitset>
#include <sstream>
#include <iomanip>

MessageEncoder::MessageEncoder()
{
    // Filling notes map.
    _notesToBinary = {
        {"DO", "001"},
        {"RE", "010"},
        {"MI", "011"},
        {"FA", "100"},
        {"SOL", "101"},
        {"LA", "110"},
        {"SI", "111"},
        {"ERROR", "000000"}
    };

    // Filling duration map.
    _durationToBinary = {
        {1, "001"},
        {2, "010"},
        {3, "011"},
        {4, "100"},
        {5, "101"},
        {6, "110"},
        {7, "111"},
        {000000, "000000"}
    }; // error code
}

MessageEncoder::~MessageEncoder()
{
    // Nothing to do.
}

std::vector<int> MessageEncoder::getMessageVectorInt()
{
    return _messageVectorInt;
}

void MessageEncoder::initEncoding(std::vector<std::pair<std::string, int> > notesVectorSplitted)
{
    std::string fullBinaryNotesString = "";
    // Getting the string with all data pairs in binary (only with '0' and '1').
    for (auto pair : notesVectorSplitted)
    {
       fullBinaryNotesString += translateVectorToString(pair.first, pair.second);
    }
    /* Once the binaryString is completed, the vector of string message to CAN BUS
     * will be created. */
    _messageVectorInt = convertBinaryStringToIntVector(fullBinaryNotesString);

}

std::string MessageEncoder::translateVectorToString(std::string note, int duration)
{
    // Checking with iterator if the note exists in the map.
    auto itNote = _notesToBinary.find(note);
    // Checking with iterator if the duration exists in the map.
    auto itDuration = _durationToBinary.find(duration);
    // String with the binary code of the pair.
    std::string binaryCodePair = "";
    // If the note is correct, it will have the corresponding value.
    if (itNote != _notesToBinary.end())
    {
        binaryCodePair = _notesToBinary.at(note);
    }
    // If the note is not correct, Error code is returned.
    else
    {
        return _notesToBinary.at("ERROR");
    }
    // If the duration is correct, it will have the corresponding value.
    if (itDuration != _durationToBinary.end())
    {
        binaryCodePair += _durationToBinary.at(duration);
    }
    // If the duration is not correct, Error code is returned.
    else
    {
        return _durationToBinary.at(000000);
    }

    return binaryCodePair;
}

std::vector<int> MessageEncoder::convertBinaryStringToIntVector(std::string binaryString)
{
    // Converting the string into a bitset.
    std::bitset<64> binaryNotesBitset(binaryString);
    // Converting Bitset into a unsigned int (64 bits).
    uint64_t uint64Number = binaryNotesBitset.to_ulong();
    // Converting unsigned int into a Hex String.
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(uint64_t)*2)
             << std::hex << uint64Number;

    std::string hex_string = stream.str();
    std::vector<int> messageVectorInt;
    // Making pairs of 2 Hex characters.
    for (int i=2; i<=16; i=i+2)
    {
        // Subpart of the message. The Hexadecimal message will be send in pairs (1 byte per pair, 2 Hex characters).
        std::string subMessage = "";
        subMessage = hex_string.c_str()[i];
        subMessage += hex_string.c_str()[i+1];
        int subMessageInt = std::stoi(subMessage, nullptr, 16);
        messageVectorInt.push_back(subMessageInt);
    }

    return messageVectorInt;
}




