#include "Communication.h"
#include <iostream>
Communication::Communication(const char* portname, int speed, int timeout){
    Connection connection(portname, speed, timeout);
    numberOfPackage = 0;
    position = 0;
}

ssize_t Communication::csend(const char* message, size_t size){
    uint8_t mesSize = size;
    uint8_t cmSize = mesSize + HEADER_SIZE + FOOTER_SIZE;
    

    char* charMessage;
    charMessage = (char*)malloc(cmSize * sizeof(char));

    //memset(charMessage, 0, cmSize);

    charMessage[0] = 0xFF;                 //1 bajt
    charMessage[1] = numberOfPackage++;                 //1 bajt
    charMessage[2] = mesSize;               //2 bajt

    strncpy(charMessage + HEADER_SIZE, message, mesSize);

    uint16_t crc;
    crc = crc16(charMessage, cmSize - FOOTER_SIZE);  

    //cout << "crc:" << crc;

    *(uint16_t*)(charMessage + cmSize - FOOTER_SIZE) = crc;

    // charMessage[cmSize - 2] = crc >> 8;    //n-1 bajt
    // charMessage[cmSize - 1] = crc;         //n-ty bajt
    ssize_t sent;
    sent = connection.cwrite(charMessage, cmSize);

    assert((sent == cmSize) && "Nie udalo sie wyslac wszystkich danych hej");

    delete charMessage;
    return sent;
}

int Communication::creceive(queue<string>& messageQueue){
    ssize_t received = connection.cread(receiveBuff + position, MAX_DATA_SIZE - position);
    
    assert((received > 0) && "Nie udalo sie pobrac danych");
    position += received;

    while(received > 0){ // wyszukiwanie nagłówka pakietu - FF
        ssize_t start = 0;
        while((*(receiveBuff + start) != 0xFF) && (start++ < position)); //clean code

        if(start == position)
            return -1;

        memmove(receiveBuff, receiveBuff + start, position - start);
        position -= start;
        

        if(position < HEADER_SIZE + FOOTER_SIZE)    //coś jest, ale to nawet nie są poprawne dane. powinnismy szukac ff
            return -1;

        uint8_t len = *(receiveBuff + HEADER_SIZE - 1);
        //printf("len =%d",len); //++testowo
        
        uint8_t packetSize = HEADER_SIZE + FOOTER_SIZE + len;

        if(position < packetSize)   //no coś tutaj najwyraźniej nie gra. Miało być tyle, a tu dupa. czegoś brakuje
            return -1;

        uint16_t crc = crc16(receiveBuff, HEADER_SIZE + len);
        uint16_t crc2 = *(uint16_t*)(receiveBuff + len + HEADER_SIZE);

        
        //printf("crc:%02x, %02x\n", crc, crc2);
        if(crc == crc2){  
            messageQueue.push(string(receiveBuff + HEADER_SIZE, len));
            memmove(receiveBuff, receiveBuff + packetSize, MAX_DATA_SIZE + HEADER_SIZE + FOOTER_SIZE - packetSize); //zamiast max_data... bylo position
            position -= packetSize;
            received -= packetSize;
        }
        //receiveBuff[0] = 0;        
    }
}

uint16_t Communication::crc16(char* data_p, int length){
    uint8_t i;
    uint16_t data;
    uint16_t crc = 0xffff;

    if(length == 0)
            return (~crc);

    do{
            for(i=0, data=(uint16_t)0xff & *data_p++; i < 8; i++, data >>= 1){
                if((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                else  
                        crc >>= 1;
            }
    }while(--length);

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);

    return (crc);
}