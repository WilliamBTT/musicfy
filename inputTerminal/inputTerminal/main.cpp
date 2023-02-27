#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "splitter.h"
#include "messageencoder.h"

using namespace std;

int main(void) {
    int line=3, t;
    string s = "";
    Splitter split;
    std::vector<std::pair<std::string, int>> notesSplit;
    MessageEncoder messageEncoder;
    std::vector<int> messageVectorInt;

    while (s != ":q")
    {
        cout << "Input message: (':q' for quit): " << endl;
        getline(cin,s); // This is to input the sentence
        cout << s << "  " << endl;
//        s = "DO-FA-------SOL-LA-RE----";
        notesSplit = split.split(s, '-');
        messageEncoder.initEncoding(notesSplit);
        messageVectorInt = messageEncoder.getMessageVectorInt();
    }
    cout << "Ending program..." << endl;
}
