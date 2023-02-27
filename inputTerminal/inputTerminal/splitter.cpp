#include "splitter.h"

Splitter::Splitter()
{
    // Nothing to do.
}

Splitter::~Splitter()
{
    // Nothing to do.
}

std::vector<std::pair<std::string, int> > Splitter::split(std::string line, char delimiter)
{
    // Vector of pairs. The pairs are composed by  [note (string), duration (int)].
    std::vector<std::pair<std::string, int>> notesVector;
    // Current note recognised.
    std::string newNote = "";
    // Current cumulative duration.
    int noteDuration = 0;

    for (unsigned long i=0; i<line.length(); ++i)
    {
        // First, check if the character is not the delimiter. Then start recognising the current note.
        if(line[i] != delimiter)
        {
            newNote += line[i];
        }
        /*
         * If the character is the delimiter, it means that is a time duration. So, the duration must be
         * increased by 1.*/
        else
        {
            ++noteDuration;
        }
        /*
         * If the character is the delimiter, AND next character is not the delimiter, AND
         * current note is not empty --> make a pair. */
        if (line[i]==delimiter  and  line[i+1] != delimiter  and  newNote != "")
        {
            notesVector.push_back(std::make_pair(newNote, noteDuration));
            newNote = "";
            noteDuration = 0;
        }
    }

    return notesVector;
}

