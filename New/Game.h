#include <sys/time.h>
#include <inttypes.h>

#define NUMBER_OF_PLAYERS 5 //pojedyńczy numer będzie odpowiadać ID czołgu.

class Point{
private:
    uint16_t posX;
    uint16_t posY;
};

class Tank{
private:
    Point position;
    uint16_t tankAngle;
    uint8_t towerAngle;
    uint8_t barrelAngle;

    struct timeval lastUpdate;
public:

};

class Tanks{
private:
    Tank tanks[NUMBER_OF_PLAYERS];
    bool visibility[NUMBER_OF_PLAYERS];
};

class Obstacle{
    Point* listOfPoints;
    int numberOfPoints;
};

class Battlefield{
    Obstacle* listOfObstacles;
    int numberOfObstacles;
};

class Wind{
private:
    uint8_t windPower;
    uint8_t windAngle;
};

class Game{
private:
    Tanks tanks;
    Battlefield battlefield;
};

