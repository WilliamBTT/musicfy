#ifndef MESSAGEDECODER_H
#define MESSAGEDECODER_H

#include <string>
#include <map>
#include <vector>

class MessageDecoder
{
public:
    /**
     * @brief MessageDecoder constructor.
     */
    MessageDecoder(std::vector<unsigned char> canFrameData);

    /**
     * @brief decode, beginning of decoding message.
     * @return final message, attribute "_messageReceived".
     */
    std::string decode();

    /**
     * @brief gettingHexString, translating can bus data frame to string.
     * @return string with hexadecimal characters.
     */
    std::string gettingHexString();


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
