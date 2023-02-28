#include "databasereader.h"
#include <iostream>
#include <cstring>

DataBaseReader::DataBaseReader(std::string databaseName)
    : _databaseName(databaseName)
{

}

int DataBaseReader::readingDataBase()
{
    int result;

    // Opening dataBase.
    result = openDataBase();
    if (result != 0)
    {
        std::cout << "Error while opening data base." << std::endl;
    }

    // Read Query.
    result = readQuery();
    if (result != 0)
    {
        std::cout << "Error during query read." << std::endl;
    }

    // Saving data into a vector.
    result = savingMelodies();
    if (result != 0)
    {
        std::cout << "Error while saving data." << std::endl;
    }

    return result;
}

int DataBaseReader::openDataBase()
{
    _rc = sqlite3_open(_databaseName.c_str(), &_db);

    if (_rc != SQLITE_OK) {
        std::cerr << "Error opening data base: " << sqlite3_errmsg(_db) << std::endl;
        sqlite3_close(_db);
        return 1;
    }
    return _rc;
}

int DataBaseReader::readQuery()
{
    // Consulta SQL para seleccionar todos los registros de la tabla
    const char* sql = "SELECT * FROM songsMelody";

    _rc = sqlite3_prepare_v2(_db, sql, -1, &_stmt, nullptr);

    if (_rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(_db) << std::endl;
        sqlite3_finalize(_stmt);
        sqlite3_close(_db);
        return 1;
    }

    return 0;
}

int DataBaseReader::savingMelodies()
{
    while (sqlite3_step(_stmt) == SQLITE_ROW) {
        // El primer campo tiene el tipo de dato int
        int id = sqlite3_column_int(_stmt, 0);
        // El segundo campo tiene el tipo de dato string
        const unsigned char* songName = sqlite3_column_text(_stmt, 1);
        // El tercer campo tiene el tipo de dato double
        const unsigned char* notes = sqlite3_column_text(_stmt, 2);

        std::string name = getStringFromUnsignedChar(songName);
        std::string melody = getStringFromUnsignedChar(notes);
        _melodiesVector.push_back(std::make_pair(name, melody));
    }
    return 0;
}

std::string DataBaseReader::getStringFromUnsignedChar(const unsigned char *input)
{
    size_t longitud = 30;
    // Crear un string vacío con la longitud necesaria
    std::string inputString(longitud, '\0');
    std::copy(input, input + longitud, inputString.begin());

    size_t length = std::strlen(inputString.c_str());
    // Eliminar los caracteres vacíos finales
    while (length > 0 && inputString[length-1] == '\0') {
        length--;
    }

    // Redimensionar la cadena al tamaño real
    inputString.resize(length);

    return inputString;
}

std::vector<std::pair<std::string, std::string> > DataBaseReader::getMelodiesVector()
{
    return _melodiesVector;
}
