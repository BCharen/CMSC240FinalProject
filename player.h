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
        Vector2 zipVelocity;
        int VertColDir = NONE;
        int HorColDir = NONE;
        bool onLadder = false;
        bool onZip = false;
        bool win = false;
        bool dead = false;
        Vector2 zipTarget;
    public:
        //x,y,width,height
        Rectangle position = {500,500,50,100};

        bool checkWin();
        void changeWinState(bool isWin);
        bool isDead();
        void changeDeadState(bool isDead);
        

        void collisionCheck(Rectangle otherRect);
        bool keyCheck(Rectangle otherRect);
        bool overlapCheck(Rectangle otherRect);
        void Draw(){
            DrawRectangleRec(position,{23,47,63,255});
        }
        bool getOnLadder();
        void setOnLadder(bool val);
        void startZip(Vector2 start, Vector2 end);
        void Update(){
            if(!onZip){

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
            else {
                position.y+=zipVelocity.y;
                position.x+=zipVelocity.x;
                if(position.x == zipTarget.x && position.y == zipTarget.y){
                    onZip = false;
                }
            }
        }
        void lrInputCheck();
};
#endif