#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "splitter.h"

using namespace std;

int main(void) {
    int line=3, t;
    string s = "";
    Splitter split;
    std::vector<std::pair<std::string, int>> notesSplit;

    while (s != ":q")
    {
        cout << "Input message: (':q' for quit): " << endl;
        getline(cin,s); // This is to input the sentence
        cout << s << "  " << endl;
        notesSplit = split.split(s, '-');
    }
    cout << "Ending program..." << endl;
}
