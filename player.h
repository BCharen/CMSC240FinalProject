
#ifndef player_h
#define player_h
#include <raylib.h>

enum Directions{
    ERROR = -1,
    UP = 0,
    LEFT,
    DOWN,
    RIGHT
};

class player{
    private:
    //x,y,width,height
        Rectangle position = {0f,0f,0f,0f};
    public:
        int collisionCheck(int dir,Rectangle otherRect);
};
#endif