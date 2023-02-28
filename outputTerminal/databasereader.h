#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <sqlite3.h>
#include <string>
#include <vector>

class DataBaseReader
{
public:
    /**
     * @brief DataBaseReader constructor.
     * @param databaseName name of data base read.
     */
    DataBaseReader(std::string databaseName);

    /**
     * @brief readingDataBase, process for reading data base.
     * @return '0' if it worked, '1' if it failed.
     */
    int readingDataBase();

    /**
     * @brief openDataBase. Open data base with sqlite3.
     * @return '0' if it worked, '1' if it failed.
     */
    int openDataBase();

    /**
     * @brief readQuery. Read query to get name and melody.
     * @return '0' if it worked, '1' if it failed.
     */
    int readQuery();

    /**
     * @brief savingMelodies
     * @return '0' if it worked, '1' if it failed.
     */
    int savingMelodies();

    /**
     * @brief getStringFromUnsignedChar
     * @param input
     * @return
     */
    std::string getStringFromUnsignedChar(const unsigned char* input);

    /**
     * @brief getMelodiesVector, getter of _melodiesVector attribute.
     * @return _melodiesVector attribute.
     */
    std::vector<std::pair<std::string, std::string>> getMelodiesVector();

private:
    /**
     * @brief _db, database instance.
     */
    sqlite3* _db;

    /**
     * @brief _databaseName, name of data base to be open.
     */
    std::string _databaseName;

    /**
     * @brief _stmt, sqlite3 statements. Loading data.
     */
    sqlite3_stmt* _stmt;

    /**
     * @brief _rc, return code that saves the return value of the query.
     */
    int _rc;

    /**
     * @brief _melodiesVector, read from data base
     */
    std::vector<std::pair<std::string, std::string>> _melodiesVector;
};

#endif // DATABASEREADER_H
