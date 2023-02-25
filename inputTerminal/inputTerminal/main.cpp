#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(void) {
    int line=3, t;
    string s = "";

    while (s != ":q")
    {
        cout << "Input message: (':q' for quit): " << endl;
        getline(cin,s); // This is to input the sentence
        cout << s << "  " << endl;
    }
    cout << "Ending program..." << endl;
}
