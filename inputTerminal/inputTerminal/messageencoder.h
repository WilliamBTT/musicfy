#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include <map>
#include <vector>

/**
 * @brief The MessageEncoder class encondes input vector of pairs [note, duration] into
 * a vector of Hexadecimal messages. These messages will be used by DataSender to send
 * data to CAN BUS.
 * 64 bits can fit in one message.
 * Each note fills in 3 bits and each duration another 3 bits.
 * So 6 bits are needed to encode thw whole pair [note, duration].
 */
class MessageEncoder
{
public:
    /**
     * @brief MessageEncoder constructor.
     */
    MessageEncoder();

    /**
     * @brief ~MessageEncoder default destructor.
     */
    ~MessageEncoder();

    /**
     * @brief getMessageVectorHex. Getter of the Message Vector in Integer.
     * @return _messageVectorHex.
     */
    std::vector<int> getMessageVectorInt();

    /**
     * @brief initEncoding. Beginning of the encoding.
     * @param notesVectorSplitted. Vector of pairs [duration, note].
     */
    void initEncoding(std::vector<std::pair<std::string, int>> notesVectorSplitted);

    /**
     * @brief translateVectorToString. Create a string of '0' and '1' with
     * note and duration data. It is the first step in this class.
     * Then the string will be converted to a vector of hexadecimal numbers.
     * For example, the message "DO--" is translated to "001010" due to
     * DO is codified by "001", and "--" is equivalent to 2 times duration
     * (codified by "010").
     * @param note. Current note to be encoded.
     * @param duration. Current duration to be encoded.
     * @return string with all data pairs [note, duration] in binary.
     */
    std::string translateVectorToString(std::string note, int duration);

    std::vector<int> convertBinaryStringToIntVector(std::string binaryString);

private:

    /**
     * @brief _notesToBinary, Map to translate Notes to binary code.
     */
    std::map<std::string, std::string> _notesToBinary;

    /**
     * @brief _durationToBinary, Map to translate duration to binary code.
     */
    std::map<int, std::string> _durationToBinary;

    /**
     * @brief _messageVectorHex, Vector with data message in integer values.
     * These integer values will be used by DataSender, to send the whole
     * Bytes to CAN BUS.
     */
    std::vector<int> _messageVectorInt;
};

#endif // MESSAGEENCODER_H
