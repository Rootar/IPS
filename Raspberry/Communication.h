#pragma once

#include "Connection.h"
#include <inttypes.h>
#include "Crc16.h"

#define CONTROLL_SIZE 4

#define BUFFER_SIZE 100

class Communication{
private:
    Connection connection;
    static uint8_t num = 0;
    unsigned char reciveBuff[BUFFER_SIZE + CONTROLL_SIZE];

public:
    Communication(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1);
    int csend(const unsigned char* message, uint8_t size);

private:
    int creceive(unsigned char* buff, uint8_t size);
};