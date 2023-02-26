#include "splitter.h"

Splitter::Splitter()
{

}

Splitter::~Splitter()
{

}

std::vector<std::pair<std::string, int> > Splitter::split(std::string line, char delimiter)
{
    std::vector<std::pair<std::string, int>> notesVector;
    std::string newNote = "";
    int noteDuration = 0;

    for (unsigned long i=0; i<line.length(); ++i)
    {
        if(line[i] != delimiter)
        {
            newNote += line[i];
        }
        else
        {
            ++noteDuration;
        }
        if (line[i]==delimiter  and  line[i+1] != delimiter  and  newNote != "")
        {
            notesVector.push_back(std::make_pair(newNote, noteDuration));
            newNote = "";
            noteDuration = 0;
        }
    }

    return notesVector;
}

