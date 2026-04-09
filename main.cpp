#include <iostream>
#include <raylib.h>
#include <string.h>
#include "player.h"
#include <array>
#include "level.cpp"
using namespace std;
Color darkGreen = {43, 51, 24, 255};
bool over=false;
player zippy = player();

level level1 = {
{Rectangle{450,800,100,50} , Rectangle{600,1200,300,50}},
{hideableObject{650,800,100,50}},
{hideableObject{650,500,100,50}}
};

void updateEnvironment(level curLevel){
    for (int i = 0; i < level1.walls.size(); i++){
        DrawRectangleRec(level1.walls[i],{42,2,57,255});
        zippy.collisionCheck(level1.walls[i]);
    }
    for (int i = 0; i < level1.keys.size(); i++){
        if(level1.keys[i].show == true){
        DrawRectangleRec(level1.keys[i].shape,{242,132,17,255});
        level1.keys[i].show = zippy.keyCheck(level1.keys[i].shape);
        level1.doors[i].show = zippy.keyCheck(level1.keys[i].shape);
        }
    }
    for (int i = 0; i < level1.doors.size(); i++){
        if(level1.doors[i].show == true){
            DrawRectangleRec(level1.doors[i].shape,{72,128,7,255});
            zippy.collisionCheck(level1.doors[i].shape);
        }
        
    }
        
} 

int main () {
    
    InitWindow(1500,1500, "Zipline Zim");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
            ClearBackground(BLACK);
            zippy.Draw();
            zippy.lrInputCheck();
            updateEnvironment(level1);
            zippy.Update();
            
            
            
        EndDrawing();
    }

    CloseWindow();
}

