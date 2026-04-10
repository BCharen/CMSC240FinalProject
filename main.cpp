#include <iostream>
#include <raylib.h>
#include <string.h>
#include "player.h"
#include <array>
#include "level.cpp"
using namespace std;
int screenWidth = 1500;
int screenHeight = 1500;
Color darkGreen = {43, 51, 24, 255};
player zippy = player();
Camera2D cam = { 0 };

//messages
int curText = -1;
char testMessage[] = "test";
/*
Each line is a different type of object. In order they are:
walls: Rectangle for position.
keys: hideableObject for position (declare as hideableObject and the parameters are the same as rectangle).
doors: same as keys. Must have an equal number of keys and doors (they check the corresponding index of keys to determine if they are open or not).
ladders: Rectangle for position.
messages: Rectangle for position. Must put a string message in the switch case at the end to be displayed.
zips: Rectangle for start location, Rectangle for end location.
*/
level level1 = {
{ Rectangle{450,800,100,50} , Rectangle{600,1200,300,50} },
{ hideableObject{650,800,100,50} },
{ hideableObject{650,500,100,50} },
{ Rectangle{425,500,50,700} },
{ Rectangle{425,475,25,25} },
{ {Rectangle{200,200,25,100},Rectangle{300,700,25,100}} }
};

Vector2 getZipStart(zipline zip){
    Rectangle pole = zip.pole1;
    return (Vector2){pole.x+(pole.width/2),pole.y};
}

Vector2 getZipEnd(zipline zip){
    Rectangle pole = zip.pole2;
    return (Vector2){pole.x+(pole.width/2),pole.y};
}

void updateEnvironment(level curLevel){

    for (int i = 0; i < level1.ladders.size(); i++){
        if(!zippy.getOnLadder()){
            zippy.setOnLadder(zippy.overlapCheck(level1.ladders[i]));
        }
        DrawRectangleRec(level1.ladders[i],{32,0,200,255});
    }
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

    for (int i = 0; i < level1.messages.size(); i++){
        if(zippy.overlapCheck(level1.messages[i])){ if(IsKeyPressed(KEY_SPACE)){curText = i;}}
        DrawRectangleRec(level1.messages[i],{255,255,255,255});
    }

    for (int i = 0; i < level1.zips.size(); i++){
        DrawRectangleRec(level1.zips[i].pole1,DARKGREEN);
        if(zippy.overlapCheck(level1.zips[i].pole1)){ if(IsKeyPressed(KEY_SPACE)){zippy.startZip(getZipStart(level1.zips[i]),getZipEnd(level1.zips[i]));}}
        DrawRectangleRec(level1.zips[i].pole2,DARKGREEN);
        if(zippy.overlapCheck(level1.zips[i].pole2)){ if(IsKeyPressed(KEY_SPACE)){zippy.startZip(getZipEnd(level1.zips[i]),getZipStart(level1.zips[i]));}}
        DrawLineEx(getZipStart(level1.zips[i]),getZipEnd(level1.zips[i]),10,DARKGREEN);
    }

        
} 
void updateCam(Camera2D *camera, player *play){
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->target = (Vector2){zippy.position.x,zippy.position.y};
}
int main () {

    cam.target = (Vector2){zippy.position.x,zippy.position.y};
    cam.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    cam.rotation = 0;
    cam.zoom = 1.0f;
    InitWindow(screenWidth,screenHeight, "Zipline Zim");
    SetTargetFPS(60);
    while (WindowShouldClose() == false){
        updateCam(&cam, &zippy);
        BeginDrawing();
            ClearBackground(BLACK);
            if(curText == -1){
            BeginMode2D(cam);
            updateEnvironment(level1);
            zippy.Draw();
            zippy.lrInputCheck();
            zippy.Update();
            EndMode2D();
            }
            else{
                //add cases for each message corresponding to index number. Just copy my text and replace the text and case number.
                
                switch (curText) {
                    case 0:
                        DrawText("test",screenWidth/2,screenHeight/2,50,{255,255,255,255});
                        break;    
                    
                    
                }
                if (IsKeyPressed(KEY_SPACE)){curText = -1;};
            }  
        EndDrawing();
    }    

    CloseWindow();
}

