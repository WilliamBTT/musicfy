#ifndef SPLITTER_H
#define SPLITTER_H

#include <iostream>
#include <vector>

/**
 * @brief The Splitter class splits input string into a vector of pairs:
 * [note, duration].
 */
class Splitter
{
public:
    // Default constructor.
    Splitter();

    // Default destructor.
    ~Splitter();

    /**
     * @brief split. Convert input string into a vector of pairs (Note, duration).
     * @param line. Input string.
     * @param delimiter. Character that separates the notes and indicates the duration
     * of each ones.
     * @return vector with the pairs "Note, duration".
     */
    std::vector<std::pair<std::string, int>> split(std::string line, char delimiter);
};

#endif // SPLITTER_H
