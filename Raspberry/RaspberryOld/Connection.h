#pragma once

#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

class cant_open_port{};

class Connection{
private:
    int set_interface_attribs(int fd, int speed, int parity, int timeout);        
    void set_blocking(int fd, int should_block, int timeout);
    int fd;

public:
    Connection(const char* portname = "/dev/ttyAMA0", int speed = B115200, int timeout = 1);

    ssize_t cwrite(const void* buff, size_t size);
    ssize_t cread(void* buff, size_t size);
};