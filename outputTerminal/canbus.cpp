#include "canbus.h"

CanBus::CanBus()
    : _ifname("vcan0")
{
    configureCanBus();
}

int CanBus::configureCanBus()
{
    // Configuring connection.
    if (configureData() == -1)
    {
        return -1;
    }

    // Creating / binding socket.
    if (bindingSocketCan() == -2)
    {
        return -2;
    }
    return 0;
}

int CanBus::configureData()
{
    // Creating socket.
    if ((_connectionInformation = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
        perror("Error while opening socket");
        return _connectionInformation;
    }
    return 0;
}

int CanBus::bindingSocketCan()
{
    strcpy(_ifr.ifr_name, _ifname);
    ioctl(_connectionInformation, SIOCGIFINDEX, &_ifr);

    // Setting address socket.
    _addr.can_family = AF_CAN;
    _addr.can_ifindex = _ifr.ifr_ifindex;

    // Linking socket to vcan.
    if (bind(_connectionInformation, (struct sockaddr *)&_addr, sizeof(_addr)) < 0) {
        perror("Error in socket bind");
        return 1;
    }
    return 0;
}
