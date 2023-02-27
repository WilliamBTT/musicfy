#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "splitter.h"
#include "messageencoder.h"
#include "datasender.h"
#include <iostream>
#include <vector>

//using namespace std;

int main(void) {
    int line=3, t;
    std::string inputLine = "";
    Splitter split;
    std::vector<std::pair<std::string, int>> notesSplit;
    MessageEncoder messageEncoder;
    std::vector<int> messageVectorInt;
    DataSender dataSender;

    if (dataSender.configureCanBus() != 0)
    {
        std::cout << "Can Bus configuration failed." <<std::endl;
        return 1;
    }

    while (inputLine != ":q")
    {
        std::cout << "Input message: (':q' for quit): " << std::endl;
        // Getting input message.
        getline(std::cin, inputLine);
//      Example of inputLine: "DO-FA-------SOL-LA-RE----";
        // Spliting message.
        if (inputLine != ":q")
        {
            notesSplit = split.split(inputLine, '-');
            // Encoding.
            messageEncoder.initEncoding(notesSplit);
            messageVectorInt = messageEncoder.getMessageVectorInt();
            // Sending data to CAN BUS.
            dataSender.setMessageVectorInt(messageVectorInt);
            dataSender.sendMessage();
        }
    }
    std::cout << "Sending ending message CAN BUS.  Ending program..." << std::endl;
    dataSender.endingProgram();

    return 0;
}
