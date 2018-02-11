
#include "Connection.h"

int Connection::set_interface_attribs(int fd, int speed, int parity, int timeout){
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

void Connection::set_blocking(int fd, int should_block, int timeout){
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0){}

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = timeout;            // 0.1 seconds read timeout

    if(tcsetattr(fd, TCSANOW, &tty) != 0){}
}

Connection::Connection(const char* portname, int speed, int timeout){
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);

    if(fd < 0) throw cant_open_port();

    set_interface_attribs(fd, speed, 0, timeout);
    set_blocking(fd, 0, timeout);
}

ssize_t Connection::cwrite(const void* buff, size_t size){
    return write(fd, buff, size);        
}

ssize_t Connection::cread(void* buff, size_t size){
    return read(fd, buff, size);
}