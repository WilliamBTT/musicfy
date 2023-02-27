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

//int DataReader::configureCanBus()
//{
//    // Configuring connection.
//    if (configureData() == -1)
//    {
//        return -1;
//    }

//    // Creating / binding socket.
//    if (bindingSocketCan() == -2)
//    {
//        return -2;
//    }
//    return 0;
//}

//int DataReader::configureData()
//{
//    // Creating socket.
//    if ((_connectionInformation = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
//        perror("Error while opening socket");
//        return _connectionInformation;
//    }
//    return 0;
//}

//int DataReader::bindingSocketCan()
//{
//    strcpy(_ifr.ifr_name, _ifname);
//    ioctl(_connectionInformation, SIOCGIFINDEX, &_ifr);

//    // Setting address socket.
//    _addr.can_family = AF_CAN;
//    _addr.can_ifindex = _ifr.ifr_ifindex;

//    // Linking socket to vcan.
//    if (bind(_connectionInformation, (struct sockaddr *)&_addr, sizeof(_addr)) < 0) {
//        perror("Error in socket bind");
//        return 1;
//    }
//    return 0;
//}

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
