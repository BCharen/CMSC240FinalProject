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
        bool overlapCheck(Rectangle otherRect);
        void Draw(){
            DrawRectangleRec(position,{23,47,63,255});
        }
        bool getOnLadder();
        void setOnLadder(bool val);
        void startZip(Rectangle start, Rectangle end);
        void Update();
        void InputCheck();

        void spawn(level* lvl);
};
#endif