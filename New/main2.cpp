#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

#define POLY 0x8408

using namespace std;

class cant_open_port{};

unsigned short crc16(char *data_p, unsigned short length){
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if(length == 0)
            return (~crc);

      do{
            for(i=0, data=(unsigned int)0xff & *data_p++; i < 8; i++, data >>= 1){
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

class Connection{
private:
    int set_interface_attribs(int fd, int speed, int parity, int timeout){
        struct termios tty;
        memset(&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0){
                return -1;
        }

        cfsetospeed(&tty, speed);
        cfsetispeed(&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive $
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = timeout;      // set timeout 1 == 0.1s

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr(fd, TCSANOW, &tty) != 0){
            return -1;
        }
        return 0;
    }
    void set_blocking(int fd, int should_block, int timeout){
        struct termios tty;
        memset(&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0){}

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = timeout;            // 0.5 seconds read timeout

        if(tcsetattr(fd, TCSANOW, &tty) != 0){}
    }
    int fd;

public:
    Connection(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1){
        fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);

        if(fd < 0) throw cant_open_port();

        set_interface_attribs(fd, speed, 0, timeout);
        set_blocking(fd, 0, timeout);
    }
    ssize_t cwrite(const void* buff, size_t size){
        return write(fd, buff, size);
    }
    ssize_t cread(void* buff, size_t size){
        return read(fd, buff, size);
    }
};




int main(){
    Connection connection;

    const char* tekst = "siemaneczke";

    int crc = crc16((char*)tekst, strlen(tekst));

    cout << crc;

    connection.cwrite(tekst, strlen(tekst));
}