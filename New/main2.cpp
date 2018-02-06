#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <inttypes.h>

#include <sys/time.h> //na czas testow
#include <cmath>

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
        if(tcgetattr(fd, &tty) != 0){
                return -1;
        }

        cfsetospeed(&tty, speed);
        cfsetispeed(&tty, speed);

        
        tty.c_cc[VMIN]  = 0;
        tty.c_cc[VTIME] = 0;

        tty.c_iflag = (IGNBRK | IGNCR);
        
        tty.c_oflag = (OPOST);

        tty.c_cflag |= (CREAD | CBAUDEX | speed);

        tty.c_lflag = 0;

        if(tcsetattr(fd, TCSANOW, &tty) != 0){
            return -1;
        }
        return 0;
    }
    void set_blocking(int fd, int should_block, int timeout){
        struct termios tty;
        memset(&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0){}

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = timeout;            // 0.1 seconds read timeout

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
        usleep(10000);
        return write(fd, buff, size);        
    }
    ssize_t cread(void* buff, size_t size){
        return read(fd, buff, size);
    }
};

class Communication{
private:
    Connection connection;
    uint8_t num;
    //unsigned char reciveBuff[BUFFER_SIZE + CONTROLL_SIZE];

public:
    Communication(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1){
        Connection connection(portname, speed, timeout);
        num = 0;
    }
    int csend(const char* message, uint8_t size){
        connection.cwrite(message, size);
    }

private:
    //int creceive(unsigned char* buff, uint8_t size);
};

int main(){
    
}

// SEKCJA KOMENTARZY

/*
    struct timeval start, end;
    gettimeofday(&start, NULL);
    */
    
    /*  Przykład użycia klasy Connection
    Connection connection;

    const char* tekst = "siemaneczke";

    int crc = crc16((char*)tekst, strlen(tekst));

    cout << crc;

    connection.cwrite(tekst, strlen(tekst));
    */



    /* przykład użycia klasy Communication oraz testy jej szybkości
    Communication communication("/dev/ttyAMA0",B115200,1);
    const char* tekst = "0123456789 ";
    
    // for(int i = 0; i < 10000; i++)        
    //     communication.csend(tekst, strlen(tekst));
    
    // for(int i = 0; i < 10000; i++)
    //     for(int j = 0; j < 5000; j++)
    //         int a = cos(i+j);

    // const char* tekst2 = "67890";
    // communication.csend(tekst2, strlen(tekst2));
    // communication.csend(tekst2, strlen(tekst2));
    // communication.csend(tekst2, strlen(tekst2));

    */

    /*
    const char* tekst3 = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70";
    Connectionv2 connection;


    char buf[] = {4, 3, 1, 2, 4, 10};
    connection.cwrite(tekst3, strlen(tekst3));

    char bufIn[100];

    while(true){
		int x = connection.cread(bufIn,sizeof(bufIn));
		if(x > 0){
            std::cout << (int)bufIn[0];
			std::cout << "tekst:" << bufIn;
            
			for(int i = 0; i < sizeof(bufIn); i++)
				bufIn[i] = '\0';
		}
	}

    //cout << "in:" << bufIn;
    gettimeofday(&end, NULL);
    cout << end.tv_sec - start.tv_sec;

    */