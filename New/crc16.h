#pragma once

#include <inttypes.h>

#define POLY 0x8408

uint16_t crc16(char* data_p, int length){
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