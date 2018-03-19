#pragma once

#include "Connection.h"
#include <inttypes.h>
#include <queue>
#include <assert.h>
#include <queue>
#include <string.h>
#include <string>

#define HEADER_SIZE 3
#define FOOTER_SIZE 2
#define MAX_DATA_SIZE 1024

using namespace std;

#define POLY 0x8408


class Communication{
private:
    Connection connection;
    uint8_t numberOfPackage;
    uint32_t position;
    char receiveBuff[HEADER_SIZE + FOOTER_SIZE + MAX_DATA_SIZE];

    uint16_t crc16(char* data_p, int length);

public:
    Communication(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1);

    //metoda transcive do wysyłania i odbierania danych

    ssize_t csend(const string& message);

    int creceive(queue<string>& messageQueue);
};