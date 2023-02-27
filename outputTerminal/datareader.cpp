#include "datareader.h"

DataReader::DataReader()
{
    _ifname = "vcan0";
//    configureCanBus();
}

DataReader::~DataReader()
{
    // Nothing to do.
}

int DataReader::readCanBus()
{
    // Reading canBus Message.
    _nbytes = read(_connectionInformation, &_frame, sizeof(struct can_frame));

    if (_nbytes < 0) {
        perror("Error al leer el socket CAN");
        return 1;
    }

    // Showing data about message received.
    // Mostrar el mensaje CAN recibido
    printf("ID de mensaje: 0x%X\n", _frame.can_id);
    printf("Longitud de datos: %d\n", _frame.can_dlc);
    printf("Datos: ");

    for (int i = 0; i < _frame.can_dlc; i++) {
        printf("%02X ", _frame.data[i]);
    }

    printf("\n");
    return 0;
}

void DataReader::readingCanBusLoop(bool &runCanBus)
{
    while(runCanBus)
    {
        readCanBus();
    }
}
