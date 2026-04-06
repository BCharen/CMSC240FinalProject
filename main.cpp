#include <iostream>
#include <raylib.h>
#include <string.h>
#include "player.h"
#include <array>
using namespace std;
Color darkGreen = {43, 51, 24, 255};
int cellSize = 100;
int cellCount = 3;
int offset = 50;
string text;
const char* c;
int curLetter = 0;
bool over=false;
player zippy = player();

Rectangle rects[] = { Rectangle{450,800,100,50} , Rectangle{600,1200,300,50}
};

void updateEnvironment(){
    for (int i = 0; i < int(sizeof(rects) / sizeof(rects[0])); i++){
        DrawRectangleRec(rects[i],{42,2,57,255});
        zippy.collisionCheck(DOWN,rects[i]);
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
    delete c;
}

