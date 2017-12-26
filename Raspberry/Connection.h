#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

class cant_open_port{};

class Connection{
private:
    int set_interface_attribs(int fd, int speed, int parity);
    void set_blocking(int fd, int should_block, int timeout);
    
public:
    Connection(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1);
}