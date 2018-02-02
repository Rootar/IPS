

//"serial=/dev/ttyAMA0; speed=19200"
//"host=127.0.0.1:2000"

class ComunicationException : public std::exception {};
class ConnectionError : public CommunicationException {};
class TimeOutError : public CommunicationException {};

#define INFINITE_WAIT (int32_t)(-1)

class ICommunication
{
    void setParameters(const std::string& params);
    void open(void);
        // ConnectionError

    std::queu<std::string> incomming_messages;
    

    bool isOpen(void) const;
    void close(void);

    void send(const std::string&);
    void send(const char*, size_t);

    std::string receive(int32_t timeout = INFINITE);
        // ConnectionError
        // TimeOutError

    bool tryReceive(std::string&, int32_t timeout = INFINITE) nothrow;

    std::string transcive(const std::string&, int32_t timeout = INFINITE);

};


class TankState
{
    std::unordered_set<std::string, time_t> cache_times;

    public:
        TankState(ICommunication& comm_device)
        {
            cache_times["gps_update"] = time(); //
        }

    Vector2f getMyPosition(void);


}

Vector2f TankState::getMyPosition(void)
{
    time_t now = time(NULL);
    time_t last = this->cache_times["gps_update"];
    if (last + 500 > now)
    {
        return this->old_gps_position;
    }

    std::string command = "{\"cmd":"get_gps_data\"}";
    this->comm.send(command);

    try
    {
        std::string response = this->comm.receive(100);

        // {"response":"get_gps_data", "x":1234, "y":1234, "a":90}

        SimpleJSONParser parser(response);

        Vector2f new_pos(   parser.getValueAsDouble("x"),
                            parser.getValueAsDouble("y"));

        this->old_gps_position = new_pos;
        this->cache_times["gps_update"] = time(NULL);
        return new_pos;

    } catch(const TimeOutError& exc)
    {
        std::cout << "Wyjątek TimeOutException: " << exc << std::end;
        return this->old_gps_position;
    }

}
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
volatile bool terminate = false;

std::mutex incomming_messages_lock;

enum class MessageClass{
    Data,
    Control
};

class MessageContainer
{
    MessageClass cls;
    std::string content;

    public:
        MessageContainer(MessageClass cls, const std::string&& content)
            : cls(cls), content(content) {          }


    public:
        std::string getContent(void) const { return this->content; }
        MessageClass getClass(void) const { return this->cls; }

    public:
        std::string toString(void) const


        cout << mc;
};


void receive_thread(void*)
{
    int fd = open("/dev/////")
    int fd = socket(...)
    connect(fd, ..)

    MessageParser parser;

    time_t last_ping_time = time();
    time_t last_pong_time = time();

    while (!terminate)
    {

        if (last_ping_time < time())
        {
            last_ping_time = time() + 5 * 1000;

            uint8_t ping_message[] = {1,2,3,4,5,6,7,8};
            send(fd, ping_message, sizeof(ping_message));
        }

        if (last_pong_time + (5+1)*1000) < time())
        {
            // komunikat
            terminate = true;
        }


        fd_set rfd, wfd, erf;

        FD_ZERO(&rfd);
        FD_ZERO(&wfd);
        FD_ZERO(&efd);

        FD_SET(fd, &rfd);

        timeval tv = {tv_sec = 1, tv_usec = 0};
        int ret = select(1-1, &rfd, &wfd, &efd, &tv);

        if (ret == 0)
        {
            continue;
        }

        if (ret == -1)
        {
            std::cout < "error = " < errno;
            perror(errno);
            exit(1);
        }

        if (!FD_ISSET(fd, &rfd))
            continue;
        
        uint8_t buffer[1024];
        size_t bytes_read = read(fd, buffer, sizeof(buffer)/*, 0  */);
        
        // bytes_read > 0
        // == 0
        // -1 

        parser.addReceivedData(buffer, bytes_read);


        while(parser.isNewContainerAvailable())
        {
            MessageContainer cmsg = parser.getFirstContainer();

            if (cmsg.getClass() == MessageClass::Data)
            {
                std::string message = cmsg.getContent();


                // readMessage odczyta wiadomość i usunie ją z kolejki
                cout << message;

                //
                    incomming_messages_lock.enter();
                    incomming_messages.push_back(message);
                    incomming_messages_lock.leave();

                //
            }

            if (cmsg.getClass() == MessageClass::Control)
            {
                std::string message = cmsg.getContent();
                SimpleJSONParser parser(message);
                std::string cmd = parser.getValueAsString("command");
                if (cmd == "pong")
                {
                    last_pong_time = time();
                }
            }
        }

    }
}


std::string receive(int timeout)
{
    time_t start = time();

    while( start + timeout > time())
    {
        int count = 0;
        incomming_messages_lock.enter();
        count = incomming_messages.size();
        incomming_messages_lock.leave(); 

        if (count == 0)
        {
            sleep(50);
            continue;
        }

        incomming_messages_lock.enter();
        std::string s = incomming_messages.front();
        incomming_message.pop_front();
        incomming_messages_lock.leave(); 
        
        return s;
    }

    throw TimeOutError("dfkgjdfklgjfklg");
}



{

    std::thread th(receive_thread);
    th.start();

    terminate = true;
    th.join();

}