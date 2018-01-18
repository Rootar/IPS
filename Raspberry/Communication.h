#pragma once

#include "Connection.h"
#include <inttypes.h>
#include "Crc16.h"

class Communication{
private:
    Connection connection;
    static uint8_t num;

public:
    Communication(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1);
    int csend(const unsigned char* message, uint8_t size);
    int creceive(unsigned char* buff, uint8_t size);
};