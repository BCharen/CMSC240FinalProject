#ifndef player_h
#define player_h

#include <raylib.h>
#include <iostream>
#include "level.h"

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
        Vector2 velocity = {0,0};
        Vector2 zipVelocity;
        int gravity = 5;
        int VertColDir = NONE;
        int HorColDir = NONE;
        bool onLadder = false;
        bool onZip = false;
        bool win = false;
        bool dead = false;
        Rectangle zipTarget;
        Texture2D* texture;
    public:
        //x,y,width,height
        player(Texture2D* playerTexture){
            texture = playerTexture;
        };
        Rectangle position = {500,500,50,100};

        void setVelocity(Vector2 v);
        bool checkWin();
        void changeWinState(bool isWin);
        bool isDead();
        void changeDeadState(bool isDead);
        vector<key> keysInInventory = {};
        bool wallJumped = false;
        void collisionCheck(Rectangle otherRect);
        bool keyCheck(Rectangle otherRect);
        bool overlapCheck(Rectangle otherRect);
        void Draw(){
            DrawRectangleRec(position,{23,47,63,255});
        }
        bool getOnLadder();
        void setOnLadder(bool val);
        void startZip(Rectangle start, Rectangle end);
        void Update(){
            if(!onZip){
                if(!onLadder || wallJumped){
                    //gravity setting
                    velocity.y += gravity * GetFrameTime() * 3.5;
                }

                if(!((VertColDir == UP && velocity.y < 0)||(VertColDir == DOWN && velocity.y > 0))){
                    position.y+=velocity.y;
                } else {
                    velocity.y = 0;
                }

                if(!((HorColDir == LEFT && velocity.x < 0)||(HorColDir == RIGHT && velocity.x > 0))){
                    position.x+=velocity.x;
                }

                VertColDir = NONE;
                HorColDir = NONE;
            }
            else {

                //zipline max speed and acceleration rate, tune as nescessary to make it feel good

                if (Vector2Length(zipVelocity) < 180){
                    zipVelocity += Vector2Normalize(Vector2Subtract({zipTarget.x, zipTarget.y}, {position.x, position.y})) * gravity * 4 * GetFrameTime();
                }
                position.x+=zipVelocity.x;
                position.y+=zipVelocity.y;
                if(CheckCollisionRecs(position,zipTarget)){
                    onZip = false;
                }
            }
        }
        void InputCheck();

        void spawn(level* lvl);
};
#endif