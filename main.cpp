#include <iostream>
#include <raylib.h>
#include <string.h>
#include "player.h"
#include <array>
#include "level.cpp"
using namespace std;

#define TEST true

#define KILLZONE 1400

Rectangle labDoorDimensions{29,23,63-29 + 1, 76-23 + 1};

int screenWidth = 1500;
int screenHeight = 1500;
Color darkGreen = {43, 51, 24, 255};
player zippy = player();
Camera2D cam = { 0 };

Texture2D pib;
Texture2D labDoor;

//messages
int curText = -1;
bool drawState = false;
Message defaultMessage{0, 0, "Default"};
Message& currentMessage = defaultMessage;

Message winMessage{0, 0, "You found pibble! Win or something"};
Message loseMessage{0, 0, "You fell off the map :("};
Message m1{600,550, "I need to find pibble, but how?"};
Message m2{3450,750, "There he is! how do I unlock this door?"};
/*
Each line is a different type of object. In order they are:
walls: Rectangle for position.
keys: hideableObject for position (declare as hideableObject and the parameters are the same as rectangle).
doors: same as keys. Must have an equal number of keys and doors (they check the corresponding index of keys to determine if they are open or not).
ladders: Rectangle for position.
messages: Rectangle for position. Must put a string message in the switch case at the end to be displayed.
zips: Rectangle for start location, Rectangle for end location.
*/


level testLevel = {
{ Rectangle{200,600,900,50} },
{ key{Rectangle{350,550,30,10}} },
{ door{Rectangle{800,450,25,150} }},
{ Rectangle{700,350,50,250} },
{ m1 },
{ {Rectangle{900,500,25,100} , Rectangle{2550,1100,25,100}} },
};

level level1 = {
{ Rectangle{0,600,900,50} , Rectangle{2500,1200,600,50} , Rectangle{3100,800,600,50}, Rectangle{3500,-300,300,50} },  
{ key{Rectangle{50,550,30,10}} , key{Rectangle{0,550,30,10}}},
{ door{Rectangle{300,450,20,150}} , door{Rectangle{3500,650,20,150}}},
{ Rectangle{3000,700,50,500},  Rectangle{3400,-400,50,1200}},
{ m1, m2 },
{ {Rectangle{800,500,25,100},Rectangle{2550,1100,25,100}} , {Rectangle{3700,-400,25,100},Rectangle{150,500,25,100}}}
};

level& currentLevel = level1;


void restartLevel(level &lvl){
    for (auto &key : lvl.keys){
        key.show = true;
    }
}

Vector2 getZipStart(zipline zip){
    Rectangle pole = zip.pole1;
    return (Vector2){pole.x+(pole.width/2),pole.y};
}

Vector2 getZipEnd(zipline zip){
    Rectangle pole = zip.pole2;
    return (Vector2){pole.x+(pole.width/2),pole.y};
}

void updateEnvironment(level &curLevel){

    //Draw Pib texture
    Rectangle source = (Rectangle){0, 0, 767, 603};
    Rectangle dest = (Rectangle){3600, 740, 50, 50};
    if (TEST){
        dest.x = 300;
        dest.y = 540;
    }
    DrawTexturePro(pib, source, dest, (Vector2){25, 25}, 45 * GetTime(),  WHITE);

    //temporary implementation of win state
    if (zippy.overlapCheck(dest)){
        zippy.changeWinState(true);
        currentMessage = winMessage;
        drawState = true;
        return;
    }

    //temporary implementation of dead state
    if (zippy.position.y > KILLZONE){
        zippy.changeDeadState(true);
        currentMessage = loseMessage;
        drawState = true;
        return;
    }

    for (auto &ladder : curLevel.ladders){
        if(!zippy.getOnLadder()){
            zippy.setOnLadder(zippy.overlapCheck(ladder));
        }
        DrawRectangleRec(ladder,{32,0,200,255});
    }

    for (auto &wall : curLevel.walls){
        DrawRectangleRec(wall,{42,2,57,255});
        zippy.collisionCheck(wall);
    }

    for (auto &key : curLevel.keys){
        if(key.show == true){
        DrawRectangleRec(key.shape,{242,132,17,255});
        key.show = zippy.keyCheck(key.shape);
        }
    }

    for (auto &door : curLevel.doors){
        if(door.correspondingKey != nullptr && door.correspondingKey->show == false){
            if (zippy.overlapCheck(door.shape)){
                DrawTexturePro(labDoor, labDoorDimensions, Rectangle{door.shape.x, door.shape.y, 75, 150}, (Vector2){0, 0}, 0,  WHITE);
            } else {
                DrawRectangleRec(door.shape, GRAY);
                zippy.collisionCheck(door.shape);
            }
        }
        else{
            DrawRectangleRec(door.shape, GRAY);
            zippy.collisionCheck(door.shape);
        }
    }

    for (auto &message : curLevel.messages){
        if(zippy.overlapCheck(message.getShape()) && IsKeyPressed(KEY_SPACE)){ 
            currentMessage = message;
            drawState = true;
        } else {
            currentMessage = defaultMessage;
            drawState = false;
        }
        message.drawTexture();
    }

    for (auto &zip : curLevel.zips){
        DrawRectangleRec(zip.pole1,DARKGREEN);
        if(zippy.overlapCheck(zip.pole1)){ if(IsKeyPressed(KEY_SPACE)){zippy.startZip(getZipStart(zip),getZipEnd(zip));}}
        DrawRectangleRec(zip.pole2,DARKGREEN);
        if(zippy.overlapCheck(zip.pole2)){ if(IsKeyPressed(KEY_SPACE)){zippy.startZip(getZipEnd(zip),getZipStart(zip));}}
        DrawLineEx(getZipStart(zip),getZipEnd(zip),10,DARKGREEN);
    }

        
} 
void updateCam(Camera2D *camera, player *play){
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->target = (Vector2){zippy.position.x,zippy.position.y};
}
int main () {

    if(TEST){
        currentLevel = testLevel; 
    }

    cam.target = (Vector2){zippy.position.x,zippy.position.y};
    cam.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    cam.rotation = 0;
    cam.zoom = 1.0f;
    InitWindow(screenWidth,screenHeight, "Zipline Zim");

    /*
    Load textures
    */

    pib = LoadTexture("textures/pibble.png"); 
    labDoor = LoadTexture("textures/door.png"); 


    //connect doors and keys

    testLevel.doors[0].correspondingKey = &testLevel.keys[0];

    level1.doors[0].correspondingKey = &level1.keys[0];
    level1.doors[1].correspondingKey = &level1.keys[1];


    SetTargetFPS(60);
    while (WindowShouldClose() == false){
        updateCam(&cam, &zippy);
        BeginDrawing();
        ClearBackground(BLACK);
            if(drawState){
                currentMessage.drawTextScreen();
                if (IsKeyPressed(KEY_SPACE)){
                    currentMessage = defaultMessage;
                    drawState = false;
                    if (zippy.isDead() || zippy.checkWin()){
                        restartLevel(currentLevel);
                        zippy.changeDeadState(false);
                        zippy.position.x = 500;
                        zippy.position.y = 500;
                    }
                }
            }else{
                BeginMode2D(cam);
                updateEnvironment(level1);
                zippy.Draw();
                zippy.lrInputCheck();
                zippy.Update();
                EndMode2D();
            }
        EndDrawing();
    }    
    CloseWindow();
}

