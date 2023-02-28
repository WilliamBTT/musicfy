#ifndef MESSAGEDECODER_H
#define MESSAGEDECODER_H

#include <string>
#include <map>
#include <vector>
#include <bitset>

class MessageDecoder
{
public:
    /**
     * @brief MessageDecoder constructor.
     */
    MessageDecoder();

    /**
     * @brief decode, beginning of decoding message.
     * @return final message, attribute "_messageReceived".
     */
    std::string decode(std::vector<unsigned char> dataInputVector);

    /**
     * @brief gettingHexString, translating can bus data frame to string.
     * @return string with hexadecimal characters.
     */
    std::string gettingHexString();

    /**
     * @brief gettingBinaryNumber, getting bitset of message received.
     * @param fullNumberHex, message received casted to string.
     * @return data bitset.
     */
    std::bitset<64> gettingBinaryNumber(std::string &fullNumberHex);

    /**
     * @brief gettingNotesDurationVector, getting vector of pairs [note,duration].
     * @param b, bitset with binary data.
     * @return vector of pairs.
     */
    std::vector<std::pair<std::string, int>> gettingNotesDurationVector(
            std::bitset<64> &b);

    /**
     * @brief gettingStringFromVector, getting final string with notes and duration.
     * @param notesDurationVector, vector of pairs [note, duration].
     */
    void gettingStringFromVector(std::vector<std::pair<std::string, int>> notesDurationVector);


private:
    /**
     * @brief _messageReceived, final message resulted of decoding can bus message.
     */
    std::string _messageReceived;

    /**
     * @brief _notesStringMap, map to translate Decimal number to his note.
     */
    std::map <int, std::string> _notesStringMap;

    /**
     * @brief _dataInputVector, input data. Is the can_frame.data.
     */
    std::vector<unsigned char> _dataInputVector;
};

#endif // MESSAGEDECODER_H
