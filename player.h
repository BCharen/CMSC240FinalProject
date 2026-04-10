#ifndef player_h
#define player_h

#include <raylib.h>
#include <iostream>
using namespace std;
enum Directions{
    NONE = -1,
    UP,
    LEFT,
    DOWN,
    RIGHT
};
class player{
    private:
        Vector2 velocity = {0,5};
        int VertColDir = NONE;
        int HorColDir = NONE;
        bool onLadder = false;
    public:
        //x,y,width,height
        Rectangle position = {500,500,50,100};
        void collisionCheck(Rectangle otherRect);
        bool keyCheck(Rectangle otherRect);
        bool overlapCheck(Rectangle otherRect);
        void Draw(){
            DrawRectangleRec(position,{23,47,63,255});
        }
        bool getOnLadder();
        void setOnLadder(bool val);
        void Update(){
            
            
            
            if(!((VertColDir == UP && velocity.y < 0)||(VertColDir == DOWN && velocity.y > 0))){
            position.y+=velocity.y;
            }
            if(!((HorColDir == LEFT && velocity.x < 0)||(HorColDir == RIGHT && velocity.x > 0))){
            position.x+=velocity.x;
            }

            VertColDir = NONE;
            HorColDir = NONE;
            onLadder = false;
        }
        void lrInputCheck();
};
#endif