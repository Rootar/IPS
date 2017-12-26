#include "Connection.h"

int Connection::set_interface_attribs(int fd, int speed, int parity, int timeout){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
            return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

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

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
            return -1;
    }
    return 0;

}

void Connection::set_blocking(int fd, int should_block, int timeout){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0){}

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = timeout;            // 0.5 seconds read timeout

    if(tcsetattr (fd, TCSANOW, &tty) != 0){}
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
