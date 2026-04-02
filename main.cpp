#include <iostream>
#include <raylib.h>
#include <string.h>

using namespace std;
Color darkGreen = {43, 51, 24, 255};
int cellSize = 100;
int cellCount = 3;
int offset = 50;
string text;
const char* c;
int curLetter = 0;
bool over=false;
int main () {
    int chosenX = 50;
    int chosenY = 50;
    const int SCREEN_WIDTH = cellCount*cellCount*cellSize;
    const int SCREEN_HEIGHT = cellCount*cellCount*cellSize;
    int filled[cellCount][cellCount];
    for (int i = 0; i < cellCount; i++){
        for (int j = 0; j < cellCount; j++){
        filled[i][j] = 2;
        }
    }

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT, "TicTacToe");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        chosenX = GetMouseX()/cellSize/cellCount;
        chosenY = GetMouseY()/cellSize/cellCount;
        if(filled[chosenX][chosenY] == 2){
            filled[chosenX][chosenY] = curLetter;
            curLetter = (curLetter+1)%2;
        }
        }


        for(int i = 0; i < cellCount; i++){
            if(filled[i][0]==curLetter&&filled[i][1]==curLetter&&filled[i][2]==curLetter){
               over = true;
            }
        }
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < cellCount; i++)
            {
                for (int j = 0; j < cellCount; j++){
                    DrawRectangleLinesEx(Rectangle{(float)i*SCREEN_WIDTH/cellCount, (float)j*SCREEN_HEIGHT/cellCount, (float)cellSize*cellCount, (float)cellSize*cellCount}, 5, darkGreen);
                    if (filled[i][j] == 0){
                        c = "X";
                    }
                    else if (filled[i][j] == 1){
                        c = "Y";
                    }
                    else {
                        c = "";
                    }
                    
                    DrawText(c, (float)i*SCREEN_WIDTH/cellCount*(3/2), (float)j*SCREEN_HEIGHT/cellCount*(3/2), 20, WHITE);
                }
            }
            if(over==true){
                DrawText("Game Over", (float)SCREEN_WIDTH/4, (float)SCREEN_HEIGHT/4, 20, WHITE);
            }
            
            
            
        EndDrawing();
    }

    CloseWindow();
    delete c;
}