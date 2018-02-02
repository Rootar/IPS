#include "Communication.h"

//  numer_paczki
//  długość_paczki
//  ||dane||
//  crc_1
//  crc_2

Communication::Communication(const char* portname, int speed, int timeout)
: connection(portname, speed, timeout){
}

int Communication::csend(const unsigned char* message, uint8_t size){
    unsigned char data[4+size];

    data[0] = num++;    //numer paczki
    data[1] = size;     //długość paczki

    for(int i = 0; i < size; i++){
        data[i + 2] = message[i];
    }

    unsigned int crc = crc16((char*)data, size + 2);
    
    data[size + 2] = crc >> 8;
    data[size + 3] = crc;

    connection.cwrite(data, size + 4);
}

int Communication::creceive(unsigned char* buff, uint8_t size){
    //unsigned char num = 
}