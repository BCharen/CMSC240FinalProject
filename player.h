
#ifndef player_h
#define player_h
#include <raylib.h>
#include <iostream>
using namespace std;
enum Directions{
    ERROR = -1,
    UP,
    LEFT,
    DOWN,
    RIGHT
};

class player{
    private:
    //x,y,width,height
        Rectangle position = {500,500,50,100};
        Vector2 velocity = {0,5};
    public:
        bool collisionCheck(int dir,Rectangle otherRect);
        void collide(Rectangle otherRect);
        void Draw(){
            DrawRectangleRec(position,{23,47,63,255});
        }
        void Update(){
            velocity.x = lrInputCheck();
            cout << velocity.x << endl;
            position.x+=velocity.x;
            position.y+=velocity.y;
        }
        int lrInputCheck();
};
#endif