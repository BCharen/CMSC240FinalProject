#include <iostream>
#include <raylib.h>
#include <string.h>
#include "player.h"
#include <array>
#include "level.h"
using namespace std;

#define TEST true
#define KILLZONE 1400
#define FPS 60

Rectangle labDoorDimensions{29,23,63-29 + 1, 76-23 + 1};
Rectangle obstacleTextureDimensions{0,0,1220,780};

int screenWidth = 1920;
int screenHeight = 1080;
Color darkGreen = {43, 51, 24, 255};
Color keyColor = {242,132,17,255};
player zippy = player();
Camera2D cam = { 0 };

Texture2D pib;
Texture2D labDoor;
Texture2D obstacleTexture;

bool toggleDrawInventory = false;
int inventoryIndex = 0;

//messages
bool drawState = false;
Message defaultMessage{0, 0, "Default"};
Message& currentMessage = defaultMessage;

Message introductionMessage = {0, 0, "Introduction"};
Message winMessage{0, 0, "You found pibble! Win or something"};
Message loseMessage{0, 0, "You fell off the map :("};
Message touchObstacleMessage{0, 0, "You touched the danger :("};
Message loadingScreen{0, 0, "Loading..."};
Message m1{150,550, "I need to find pibble, but how?"};
Message m2{3450,750, "How do I unlock this door?"};
/*
Each line is a different type of object. In order they are:
walls: Rectangle for position.
keys: hideableObject for position (declare as hideableObject and the parameters are the same as rectangle).
doors: same as keys. Must have an equal number of keys and doors (they check the corresponding index of keys to determine if they are open or not).
ladders: Rectangle for position.
messages: Rectangle for position. Must put a string message in the switch case at the end to be displayed.
zips: Rectangle for start location, Rectangle for end location.
Obstacle: Width, height, speed, starting position and ending position (make sure starting position height >= ending position height)
spawn: spawnpoint
objectiveCoordinates: Coordinate of objective
*/

level win = {
{Rectangle{200,600,900,50}},
{},
{},
{},
{},
{},
{},
{300,500},
{{900, 540, 50, 50}, nullptr}
};

level testLevel = {
{ Rectangle{200,600,900,50} },
{ key{Rectangle{350,550,30,10}} },
{ door{Rectangle{800,450,20,150} }},
{ Rectangle{700,350,50,250} },
{ m1 },
{ },
{Obstacle{200,50,50,{300,0},{200,500}}},
{500, 500},
{{900,500,25,100} , {3500,1300,25,100}, &win}
};

level level2 = {
{ Rectangle{0,600,900,50} , Rectangle{2500,1200,600,50} , Rectangle{3100,800,600,50}, Rectangle{3500,-300,300,50} , Rectangle{3500,600,400,50} },  
{ key{Rectangle{50,550,30,10}} , key{Rectangle{0,550,30,10}}},
{ door{Rectangle{300,450,20,150}} , door{Rectangle{3500,650,20,150}}},
{ Rectangle{3000,700,50,500},  Rectangle{3400,-400,50,1200}},
{ m2 },
{ Zipline{Rectangle{800,500,25,100},Rectangle{2550,1100,25,100}} , Zipline{Rectangle{3700,-400,25,100},Rectangle{150,500,25,100}}},
{},
{500, 500},
{{3600,700,25,100} , {5000,900,25,100}, &win}
};

level level1 = {
{ Rectangle{-800,600,1100,1000}, {1500,800,500,1000} },
{  },
{  },
{  },
{ m1 },
{ Zipline{Rectangle{250,500,25,100},Rectangle{1550,700,25,100}} },
{},
{50,500},
{{1900, 700, 25, 100}, {3000, 900, 25, 100}, &level2}
};

vector<level*> levelSet1 = {&level1,&level2,&win};
vector<level*> levelSetTest = {&testLevel,&win};


//These are pointers, be careful when referencing them to level objects
vector<level*>* currentLevelSet;
level* currentLevel;
level* startingLevel;


void restartLevel(level* lvl){
    for (auto &key : (*lvl).keys){
        key.setShow(true);
        zippy.keysInInventory.clear();
    }
}

void restartGame(vector<level*>* lvls){
    for (auto &level : *lvls){
        restartLevel(level);
    }
}

void drawInventory(){
    if(IsKeyPressed(KEY_ONE)){
        inventoryIndex = 0;
    } else if (IsKeyPressed(KEY_TWO)){
        inventoryIndex = 1;
    } else if (IsKeyPressed(KEY_THREE)){
        inventoryIndex = 2;
    } else if (IsKeyPressed(KEY_FOUR)){
        inventoryIndex = 3;
    } else if (IsKeyPressed(KEY_FIVE)){
        inventoryIndex = 4;
    } else if (IsKeyPressed(KEY_SIX)){
        inventoryIndex = 5;
    }
    DrawRectangleRec((Rectangle){50, 50, 600, 120}, GRAY);
    DrawRectangleRec((Rectangle){50, 50, 600, 20}, darkGreen);
    DrawRectangleRec((Rectangle){50, 150, 600, 20}, darkGreen);
    DrawRectangleRec((Rectangle){50, 50, 20, 120}, darkGreen);
    DrawRectangleRec((Rectangle){150, 50, 20, 120}, darkGreen);
    DrawRectangleRec((Rectangle){250, 50, 20, 120}, darkGreen);
    DrawRectangleRec((Rectangle){350, 50, 20, 120}, darkGreen);
    DrawRectangleRec((Rectangle){450, 50, 20, 120}, darkGreen);
    DrawRectangleRec((Rectangle){550, 50, 20, 120}, darkGreen);
    DrawRectangleRec((Rectangle){650, 50, 20, 120}, darkGreen);
    switch (inventoryIndex) {
        case 0:
            DrawRectangleRec((Rectangle){70, 70, 80, 80}, WHITE);
            break;
        case 1:
            DrawRectangleRec((Rectangle){170, 70, 80, 80}, WHITE);
            break;
        case 2:
            DrawRectangleRec((Rectangle){270, 70, 80, 80}, WHITE);
            break;
        case 3:
            DrawRectangleRec((Rectangle){370, 70, 80, 80}, WHITE);
            break;
        case 4:
            DrawRectangleRec((Rectangle){470, 70, 80, 80}, WHITE);
            break;
        case 5:
            DrawRectangleRec((Rectangle){570, 70, 80, 80}, WHITE);
            break;
        default:
            break;
    }
    if (inventoryIndex < (int)zippy.keysInInventory.size()){
    DrawText(zippy.keysInInventory[inventoryIndex].name.c_str(), 50, 200, 50, WHITE);
    }
    int drawIndex = 0;
    for (auto item : zippy.keysInInventory){
        DrawRectangleRec((Rectangle){95.0f + 100*drawIndex, 105.0f, item.shape.width, item.shape.height}, keyColor);
        drawIndex++;
    }
}

void updateEnvironment(level &curLevel){

    //Draw Pib texture
    Rectangle source = (Rectangle){0, 0, 767, 603};

    //temporary implementation of win state
    if(curLevel.objective.isThisPib()){
        DrawTexturePro(pib, source, curLevel.objective.getPibShape(), (Vector2){25, 25}, 45 * GetTime(),  WHITE);
        if (zippy.overlapCheck(curLevel.objective.getPibShape())){
            zippy.changeWinState(true);
            currentMessage = winMessage;
            drawState = true;
            return;
        }
    } else {
        DrawRectangleRec(curLevel.objective.getPoleOne(),PINK);
        DrawRectangleRec(curLevel.objective.getPoleTwo(),PINK);
        DrawLineEx(curLevel.objective.getZipStart(),curLevel.objective.getZipEnd(),10,PINK);

        if(zippy.overlapCheck(curLevel.objective.getPoleOne())){ 
            if(IsKeyPressed(KEY_SPACE)){
                zippy.startZip(curLevel.objective.pole1,curLevel.objective.pole2);
            }
        }

        if(zippy.overlapCheck(curLevel.objective.getPoleTwo())){
            currentMessage = loadingScreen;
            currentLevel = curLevel.objective.getConnectedLevel();
            drawState = true;
            zippy.spawn(currentLevel);
        }
    }

    //temporary implementation of dead state
    if (zippy.position.y > KILLZONE){
        zippy.changeDeadState(true);
        currentMessage = loseMessage;
        drawState = true;
        return;
    }

    if(IsKeyPressed(KEY_TAB)){
        toggleDrawInventory = !toggleDrawInventory;
    }

    zippy.setOnLadder(false);
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
            DrawRectangleRec(key.shape, keyColor);
            if (zippy.overlapCheck(key.shape)){
                key.setShow(false);
                zippy.keysInInventory.push_back(key);
            }
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
            break;
        }
        message.drawTexture();
    }

    for (auto &zip : curLevel.zips){
        DrawRectangleRec(zip.pole1,DARKGREEN);
        if(zippy.overlapCheck(zip.pole1)){ 
            if(IsKeyPressed(KEY_SPACE)){
                zippy.startZip(zip.pole1,zip.pole2);
            }
        }
        DrawRectangleRec(zip.pole2,DARKGREEN);
        if(zippy.overlapCheck(zip.pole2)){ 
            if(IsKeyPressed(KEY_SPACE)){
                zippy.startZip(zip.pole1,zip.pole2);
            }
        }
        DrawLineEx(zip.getZipStart(),zip.getZipEnd(),10,DARKGREEN);
    }

    for (auto &obstacle : curLevel.obstacles){
        obstacle.obstacleUpdate();
        if(obstacle.show == true){
            if(obstacle.isDangerous()){
                DrawTexturePro(obstacleTexture, obstacleTextureDimensions, obstacle.shape, (Vector2){0, 0}, 0,  WHITE);
                if(zippy.overlapCheck(obstacle.shape)){
                    zippy.changeDeadState(true);
                    currentMessage = touchObstacleMessage;
                    drawState = true;
                    return;
                }
            } else {
                DrawRectangleRec(obstacle.shape,{42,2,57,255});
                zippy.collisionCheck(obstacle.shape);
            }
        }
    }

        
} 
void updateCam(Camera2D *camera, player *play){
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->target = (Vector2){ zippy.position.x,zippy.position.y };
}
int main () {

    if(TEST){
        currentLevelSet = &levelSetTest; 
    } else {
        currentLevelSet = &levelSet1; 
    }

    startingLevel = (*currentLevelSet)[0];
    currentLevel = startingLevel;

    zippy.spawn(currentLevel);

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
    obstacleTexture = LoadTexture("textures/danger.png"); 


    //connect doors and keys

    testLevel.doors[0].correspondingKey = &testLevel.keys[0];
    testLevel.keys[0].name = "Test Level Key";

    level2.doors[0].correspondingKey = &level2.keys[0];
    level2.keys[0].name = "First Door Key";
    level2.doors[1].correspondingKey = &level2.keys[1];
    level2.keys[1].name = "Second Door Key";

    //Introduction screen

    currentMessage = introductionMessage;
    drawState = true;

    SetTargetFPS(FPS);
    while (WindowShouldClose() == false){
        updateCam(&cam, &zippy);
        BeginDrawing();
        ClearBackground(BLACK);
            if(drawState){
                currentMessage.drawTextScreen();
                if (IsKeyPressed(KEY_SPACE)){
                    currentMessage = defaultMessage;
                    drawState = false;
                    if (zippy.isDead()){
                        restartLevel(currentLevel);
                        zippy.changeDeadState(false);
                        zippy.changeWinState(false);
                        zippy.spawn(currentLevel);
                    }
                    if (zippy.checkWin()){
                        restartGame(currentLevelSet);
                        zippy.changeDeadState(false);
                        zippy.changeWinState(false);
                        currentLevel = startingLevel;
                        zippy.spawn(startingLevel);
                    }
                }
            } else {
                BeginMode2D(cam);
                updateEnvironment(*currentLevel);
                zippy.Draw();
                zippy.lrInputCheck();
                zippy.Update();
                EndMode2D();

                if(toggleDrawInventory){
                    drawInventory();
                }
            }
        EndDrawing();
    }    
    CloseWindow();
}

