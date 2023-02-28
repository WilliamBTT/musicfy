#include "messagedecoder.h"
#include <sstream>


MessageDecoder::MessageDecoder()
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

std::string MessageDecoder::decode(std::vector<unsigned char> dataInputVector)
{
    // Setting input Vector of canBus data.
    _dataInputVector = dataInputVector;

    // Getting string of data frame CAN BUS.
    std::string numberHex = gettingHexString();

    // Getting binary number of message received (bitset).
    std::bitset<64> binaryNumber = gettingBinaryNumber(numberHex);

    // Getting vector of pairs [note, duration].
    std::vector<std::pair<std::string, int>> notesDurationVector =
            gettingNotesDurationVector(binaryNumber);

    // Getting final string with notes and duration. It will set "_messageReceived" attribute.
    gettingStringFromVector(notesDurationVector);

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

std::bitset<64> MessageDecoder::gettingBinaryNumber(std::string &fullNumberHex)
{
    std::stringstream ss;
    ss << std::hex << fullNumberHex;
    long unsigned numberHex;
    ss >> numberHex;
    std::bitset<64> b(numberHex);

    return b;
}

std::vector<std::pair<std::string, int> > MessageDecoder::gettingNotesDurationVector(std::bitset<64> &b)
{
    std::vector<std::pair<std::string, int>> notesDurationVector;
    for (int i=0; i<10; ++i)
    {
        int limDurationInf = 61-6*i;
        int limDurationSup = 63-6*i;
        int limNoteInf = 58-6*i;
        int limNoteSup = 60-6*i;
        std::bitset<3>durationBit(b.to_string().substr(limDurationInf, limDurationSup));
        std::bitset<3>noteBit(b.to_string().substr(limNoteInf, limNoteSup));
        unsigned durationDec = durationBit.to_ullong();
        unsigned noteDec = noteBit.to_ullong();
        std::string noteString;
        if (noteDec != 0){
            noteString = _notesStringMap.at(noteDec);
        }
        else
        {
            noteString = "";
        }

        notesDurationVector.push_back(std::make_pair(noteString, durationDec));
    }

    return notesDurationVector;
}

void MessageDecoder::gettingStringFromVector(std::vector<std::pair<std::string, int> > notesDurationVector)
{
    std::string finalMessage="";
    for (int i=9; i>=0; --i)
    {
        finalMessage = finalMessage + notesDurationVector[i].first;
        for (int j=0; j<notesDurationVector[i].second; ++j)
        {
            finalMessage = finalMessage + "-";
        }
    }

    _messageReceived = finalMessage;
}

