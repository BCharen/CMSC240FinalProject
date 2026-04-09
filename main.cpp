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

level level1 = {{Rectangle{450,800,100,50} , Rectangle{600,1200,300,50}},{},{}};

void updateEnvironment(){
    for (int i = 0; i < level1.walls.size(); i++){
        DrawRectangleRec(level1.walls[i],{42,2,57,255});
        DrawRectangleRec(level1.keys[i],{242,132,17,255});
        DrawRectangleRec(level1.doors[i],{72,128,7,255});

        zippy.collisionCheck(level1.walls[i]);
    }
} 

int main () {
    
    InitWindow(1500,1500, "Zipline Zim");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
            ClearBackground(BLACK);
            zippy.Draw();
            updateEnvironment();
            zippy.Update();
            
            
            
        EndDrawing();
    }

    CloseWindow();
}

