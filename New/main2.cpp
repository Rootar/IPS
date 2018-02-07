#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <inttypes.h>

#include <queue>

#include <sys/time.h> //na czas testow usleep(10000);
#include <cmath>

#define POLY 0x8408
#define HEADER_SIZE 3
#define FOOTER_SIZE 2
#define MAX_DATA_SIZE 4096


using namespace std;

class cant_open_port{};

 uint16_t crc16(const char *data_p, unsigned short length){
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
        
        tty.c_lflag = 0;        // zerujemy flagi lokalne, w tym ICANON
        
        tty.c_cc[VMIN]  = 0;    // nie blokujemy czytania, wszystko działa od razu
        tty.c_cc[VTIME] = 0;

        tty.c_iflag = (IGNBRK | IGNCR); //ignorujemy break i cr
        
        tty.c_oflag = ~OPOST;  // wyłączamy pzetwarzanie

        tty.c_cflag |= (CREAD | CBAUDEX | speed); //możemy czytać, duże prędkości, prędkość

        

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
        return write(fd, buff, size);        
    }
    ssize_t cread(void* buff, size_t size){
        return read(fd, buff, size);
    }
};

// ff
//  numer_paczki 1B
//  długość_paczki 1B
//  ||dane|| n
//  crc_1
//  crc_2

class Communication{
private:
    Connection connection;
    uint8_t numberOfPackage;
    uint32_t position;
    unsigned char receiveBuff[HEADER_SIZE + FOOTER_SIZE + MAX_DATA_SIZE];

public:
    Communication(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1){
        Connection connection(portname, speed, timeout);
        numberOfPackage = 0;
        position = 0;
    }

    //metoda transcive do wysyłania i odbierania danych

    ssize_t csend(const string& message){
        uint8_t mesSize = message.size();
        uint8_t cmSize = mesSize + HEADER_SIZE + FOOTER_SIZE;
        

        char* charMessage;
        charMessage = (char*)malloc(cmSize * sizeof(char));

        //memset(charMessage, 0, cmSize);

        charMessage[0] = 0xFF;                 //1 bajt
        charMessage[1] = numberOfPackage++;                 //1 bajt
        charMessage[2] = mesSize;               //2 bajt

        strcpy(charMessage + HEADER_SIZE, message.c_str());

        uint16_t crc;
        crc = crc16(charMessage, cmSize - FOOTER_SIZE);  

        cout << "crc:" << crc;

        *(uint16_t*)(charMessage + cmSize - FOOTER_SIZE) = crc;

        // charMessage[cmSize - 2] = crc >> 8;    //n-1 bajt
        // charMessage[cmSize - 1] = crc;         //n-ty bajt
        ssize_t sent;
        sent = connection.cwrite(charMessage, cmSize);

        assert((sent == cmSize) && "Nie udalo sie wyslac wszystkich danych hej");

        return sent;
    }

private:
    char* concatenation(){
        charMessage[0] = num++;                 //1 bajt
        charMessage[1] = mesSize;               //2 bajt
         //x bajtów - dane   TU SKOŃCZYŁEm
    }
    int creceive(queue<string>& messageQueue){
        ssize_t received;
        received = cread(receiveBuff + position, MAX_DATA_SIZE - position);
        assert((received > 0) && "Nie udalo sie pobrac danych");
        position += received;

        while(true){ // wyszukiwanie nagłówka pakietu - FF
            ssize_t start = 0;
            while((*(receiveBuff + start) != 0xFF) && (start++ < position)); //clean code
            
            if(start == position)
                return -1;
            

            memmove(receiveBuff, receiveBuff + start, position - start);
            position -= start;

            if(position < HEADER_SIZE + FOOTER_SIZE)
                return -1;

            uint8_t len = *(receiveBuff + HEADER_SIZE - 1);
            packetSize = HEADER_SIZE + FOOTER_SIZE + len;
            if(position < packetSize)
                return -1;

            uint16_t crc = crc16(receiveBuff, HEADER_SIZE + size);

            uint16_t crc2 = *(uint16_t*)(receiveBuff + len + HEADER_SIZE);

            printf("crc:%04x, %04x\n", crc, crc2);

            if(crc == crc2){           
                messageQueue.push(string(receiveBuff + HEADER_SIZE, len));
                memmove(receiveBuff, receiveBuff + packetSize, position - packetSize);
                position -= packetSize;
            }
            receiveBuff[0] = 0;
        }
    }
};

int main(){
    queue<string> kolejka;
    Communication com;
    
    com.csend(kolejka.front());
    while(true){
    com.creceive(kolejka);

    cout << kolekja.back();
    }
}

// SEKCJA KOMENTARZY.

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