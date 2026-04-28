#include <iostream>
#include <raylib.h>
#include <string.h>
#include "player.h"
#include "AudioManager.h"
#include <array>
#include "level.h"
using namespace std;

#define TEST false
#define KILLZONE 2000
#define FPS 60

AudioManager songs = AudioManager();

Rectangle defaultRectangle{0,0,0,0};
Rectangle labDoorDimensions{29,23,63-29 + 1, 76-23 + 1};
Rectangle obstacleTextureDimensions{0,0,1220,780};
Rectangle currentLadder = defaultRectangle;

Texture2D pib;
Texture2D labDoor;
Texture2D obstacleTexture;
Texture2D defaultMessageTexture;
Texture2D note;
Texture2D pointOfInterest;
Texture2D playerTexture;
Texture2D playerZippingTexture;

int screenWidth = 1920;
int screenHeight = 1080;
Color darkGreen = {43, 51, 24, 255};
Color keyColor = {242,132,17,255};
player zippy = player(&playerTexture);
Camera2D cam = { 0 };

bool toggleDrawInventory = false;
int inventoryIndex = 0;

//messages
bool drawState = false;
bool readState = false;
int readIndex = 0;
Message defaultMessage{0, 0, "Default", &defaultMessageTexture};
Message& currentMessage = defaultMessage;

Message introductionMessage = {0, 0, "Press space to interact with everything", &defaultMessageTexture};
Message winMessage{0, 0, "You found pibble!", &defaultMessageTexture};
Message loseMessage{0, 0, "You fell off the map :(", &defaultMessageTexture};
Message touchObstacleMessage{0, 0, "You touched the danger :(", &defaultMessageTexture};
Message loadingScreen{0, 0, "Loading...", &defaultMessageTexture};
Message m1{150,550, "It's getting dark, I need to find a way down \nI remember seeing a zipline around here", &pointOfInterest};
Message m2{3450,750, "How do I unlock this door?", &pointOfInterest};  
Message m3{-100,-1550, "What is this building?\nI see a large logo in the distance\nP.R.F?", &pointOfInterest};
Message l1{-900,1750, "September 29th, 2024 \nOrder to P.R.F: \n50 cans Sweet Corn, 100 cans Beans, 100 cans Chili,\n80 cans Tomato Soup, 20 cans Bacon, \nDeliver by September 30th 10:00 am.\nSidenote: What an unusual order for a company party.\nCustomer said we aren't allowed to enter any other room. \nI guess I won't question it.", &note};
Message l2{2300, 500, "September 27th, 2024 \nThere's a company party next Monday night in the basement.\nThe way everyone talks about it that feels off.\nHR asked us to fill a form so they can decide the menu.\nThe options were all canned food, which makes no sense.\nMr. Spencer said it's to celebrate recent research advances?\nand made a point of telling me to attend.\nI'm supposed to be down there at 7:00.\n I'll go anyway. It's just a party.", &note};
Message l3{-2400, -1050, "Welcome, esteemed visitors, to P.R.F!\nPlease remain in approved visitor areas at all times\nand follow staff instructions without delay.\nFor your safety, do not enter restricted laboratories,\nstorage rooms, or basement levels\nunless escorted by authorized personnel.\nPhotography, recording, and contact with research specimens\nare strictly prohibited.\nAny unusual entity should be reported to security immediately.", &note};
Message l4{2750, -950, "September 30th\nI've been ordered to guard the exits\nduring the party tonight and check for attendance.\nDon't know why that would be necessary\nespecially for a company party.\nAnyways, orders are orders, I don't wanna get fired.", &note};
Message l5{0, -550, "August 13th,\nSubject: Phase IV Results: Behavioral Conversion Success\nTo: Oswald Spencer\nI am pleased to report that Phase IV has met all objectives.\nSubjects consistently exhibit the target behavioral profile:\nheightened fixation, rapid response, and sustained engagement.\nMost notably, external perception remains advantageous.\nField observers uniformly underestimate the subjects contact.\nContainment protocols required minor revisions,\nbut the current measures are sufficient\nprovided they are strictly followed.\nI would strongly advise against unsupervised exposure,\nregardless of prior familiarity with the source animals.\nAwaiting your authorization to proceed to distribution.\nDr. Valessa Voss, Head of Research Department P.R.F", &note};


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

// level level3 = {
// { Rectangle{0,600,900,50} , Rectangle{2500,1200,600,50} , Rectangle{3100,800,600,50}, Rectangle{3500,-300,300,50} , Rectangle{3500,600,400,50} },  
// { key{Rectangle{50,550,30,10}} , key{Rectangle{0,550,30,10}}},
// { door{Rectangle{300,450,20,150}} , door{Rectangle{3500,650,20,150}}},
// { Rectangle{3000,700,50,500},  Rectangle{3400,-400,50,1200}},
// { m2 },
// { Zipline{Rectangle{800,500,25,100},Rectangle{2550,1100,25,100}} , Zipline{Rectangle{3700,-400,25,100},Rectangle{150,500,25,100}}},
// {},
// {500, 500},
// {{3600,700,25,100} , {5000,900,25,100}, &win}
// };
level level3 = {
{Rectangle{0,0,2900,200}, Rectangle{0,600,2900,200}, Rectangle{0,2000,3200,200}, // mass h floors
Rectangle{0,800,200,1400}, Rectangle{2700,1400,200,600}, // mass v floors
Rectangle{800,200,100,250}, Rectangle{2100,200,100,250}, Rectangle{2800,200,100,250}, Rectangle{2100,800,100,250}, Rectangle{2800,800,100,250}, // door tops
Rectangle{200,1000,400,200}, Rectangle{400,1200,200,200}, Rectangle{1000,1100,200,300}, Rectangle{1600,1200,200,200}, Rectangle{2100,1200,800,200}, // platforms row 1
Rectangle{400,1600,200,200}, Rectangle{1000,1600,200,200}, Rectangle{1600,1600,700,200}, // platforms row 2
Rectangle{2100,1400,100,50}, Rectangle{2100,1800,100,50}, // short door tops
},
{key{Rectangle{285,1945,30,10}}, key{Rectangle{2485,1945,30,10}}, key{Rectangle{3035,1945,30,10}}}, 
{door{Rectangle{2140,450,20,150}}, door{Rectangle{2840,450,20,150}}, door{Rectangle{2140,1050,20,150}}, door{Rectangle{2840,1050,20,150}}, door{Rectangle{2140,1450,20,150}}, door{Rectangle{2140,1850,20,150}}, },
{Rectangle{625,1000,50,1000}, Rectangle{925,1100,50,900}, Rectangle{1225,1100,50,900}, Rectangle{1525,1200,50,800}, Rectangle{2025,1200,50,400}, Rectangle{2925,400,50,1600}, Rectangle{3125,400,50,1600}, },
{},
{},
{Obstacle{80,80,50,{610,800},{610,1900}}, Obstacle{80,80,60,{910,900},{910,1900}}, Obstacle{80,80,70,{1210,900},{1210,1900}}, Obstacle{80,80,80,{1510,1000},{1510,1900}}, 
Obstacle{80,80,40,{310,1910},{2010,1911}}, 
Obstacle{80,80,60,{2910,100},{2910,1900}}, Obstacle{80,80,40,{3010,100},{3010,1900}}, Obstacle{80,80,80,{3110,100},{3110,1900}}, },
{300,900},
{{0, 540, 50, 50}, &win}
};

level level2 = {
{Rectangle{-5000,-1000,3000,3000}, Rectangle{-1300,-1200,1300,200}, Rectangle{-1300,-1190,600,490}, Rectangle{-600,-725,1000,25}, Rectangle{500,-1200,600,500},Rectangle{100,-1200,1000,200}, Rectangle{-250,-1500,525,25}, Rectangle{-250,-1490,25,190}, Rectangle{250,-1490,25,190},
Rectangle{-2800,-1200,30,200}, Rectangle{-2800,-1200,100,30}, Rectangle{-2800,-1115,100,30}, Rectangle{-2730,-1200,30,115}, Rectangle{-2670,-1200,30,200}, Rectangle{-2670,-1200,100,30}, Rectangle{-2670,-1115,100,30}, Rectangle{-2600,-1200,30,115}, Rectangle{-2620,-1085,30,85}, Rectangle{-2540,-1200,30,200}, Rectangle{-2540,-1200,100,30}, Rectangle{-2540,-1115,85,30},
Rectangle{2000,-900,500,200}, Rectangle{2000,-550,1000,3000}, Rectangle{2600,-900,400,3000}, Rectangle{2300,-1200,525,25}, Rectangle{2300,-1190,25,140}, Rectangle{2800,-1190,25,340},
Rectangle{-1300,-500,1500,300}, Rectangle{300,-500,800,300}, Rectangle{-1300,-490,900,2500}, Rectangle{-400,-700,25,50}, Rectangle{375,-700,25,50},
Rectangle{-400,0,1500,2000}},
{key{Rectangle{2400,-950,30,10}}},
{door{Rectangle{-250,-1350,25,150}}, door{Rectangle{250,-1350,25,150}}, door{Rectangle{2300,-1050,25,150}}, door{Rectangle{-400,-650,25,150}}, door{Rectangle{375,-650,25,150}}},
{Rectangle{25,-1200,50,400}, Rectangle{-675,-725,50,225}, Rectangle{425,-725,50,225}, Rectangle{2525,-900,50,350}, Rectangle{225,-500,50,500}},
{ m3, l3, l4, l5},
{Zipline{Rectangle{-10000,-3000,25,100},Rectangle{0,-1600,25,100}} , Zipline{Rectangle{-1250,-1300,25,100},Rectangle{-2050,-1100,25,100}}, Zipline{Rectangle{-2050,-1100,25,100},Rectangle{-1250,-600,25,100}}, Zipline{Rectangle{1050,-1300,25,100},Rectangle{2050,-1000,25,100}}, Zipline{Rectangle{2050,-650,25,100},Rectangle{1050,-600,25,100}}},
{},
{0,-1600},
{{1050, -100, 25, 100}, {5200, 2000, 25, 100}, &level3}
};

level level1 = {
{ Rectangle{-1150,600,1450,1000}, Rectangle{-2400,600,1100,2000}, Rectangle{-2400,1800,2700,1000}, Rectangle{1500,800,350,400}, Rectangle{1500,1400,2000,2000}, Rectangle{2000,800,2000,2000}, Rectangle{2200,300,25,400}, Rectangle{2200,300,800,25}, Rectangle{2200,550,700,25}, Rectangle{3000,300,25,400}},
{ key{Rectangle{-1000,1750,30,10}}, key{Rectangle{2250,500,30,10}} },
{ door{Rectangle{2200,650,25,150}}, door{Rectangle{3000,650,25,150}} },
{ Rectangle{-1265,600,80,1200}, Rectangle{2925,550,50,250} },
{ m1, l1, l2 },
{ Zipline{Rectangle{250,500,25,100},Rectangle{1550,700,25,100}}, Zipline{Rectangle{1550,1300,25,100},Rectangle{250,1700,25,100}} },
{},
{50,500},
{{3950, 700, 25, 100}, {7200, 900, 25, 100}, &level2}
};

vector<level*> levelSet1 = {&level1,&level2,&level3,&win};
vector<level*> levelSetTest = {&testLevel,&win};


//These are pointers, be careful when referencing them to level objects
vector<level*>* currentLevelSet;
level* currentLevel;
level* startingLevel;

/**
 * @brief Resets all the keys back to their initial position
 * @param lvl level to reset
 */
void restartLevel(level* lvl){
    for (auto &key : (*lvl).keys){
        key.setShow(true);
    }
}

/**
 * @brief restarts all levels in the levelSet
 * @param lvls the levelset being used
 */
void restartGame(vector<level*>* lvls){
    for (auto &level : *lvls){
        restartLevel(level);
    }
}

/**
 * @brief displays the inventory
 */
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

/**
 * @brief Updates the state of everything in the current level
 * @param curLevel the level currently running 
 */
void updateEnvironment(level &curLevel){
    if(zippy.isZipping()){
        zippy.changeTexture(&playerZippingTexture);
    } else {
        zippy.changeTexture(&playerTexture);
    }

    //Draw Pib texture
    Rectangle source = (Rectangle){0, 0, 767, 603};

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
        DrawRectangleRec(ladder,{120, 85, 55, 255});

        if(zippy.overlapCheck(currentLadder) && !IsKeyPressed(KEY_SPACE)){
            continue;
        } else {
            if (IsKeyPressed(KEY_SPACE) && zippy.overlapCheck(currentLadder)){
                zippy.setVelocity({0,-5});
            }
            zippy.setOnLadder(false);
            currentLadder = defaultRectangle;
        }
        
        if(!zippy.getOnLadder() && zippy.overlapCheck(ladder) && (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))){
            zippy.setOnLadder(true);
            currentLadder = ladder;
        }
    }

    for (auto &wall : curLevel.walls){
        DrawRectangleRec(wall,{55, 38, 24, 255});
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
        if(door.correspondingKey == nullptr){
            if (zippy.overlapCheck(door.shape)){
                DrawTexturePro(labDoor, labDoorDimensions, Rectangle{door.shape.x, door.shape.y, 75, 150}, (Vector2){0, 0}, 0,  WHITE);
            } else {
                DrawRectangleRec(door.shape, GRAY);
                zippy.collisionCheck(door.shape);
            }
        }
        else if (door.correspondingKey->show == false){
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
            readState = true;
            break;
        }
        message.drawTexture();
    }

    for (auto &zip : curLevel.zips){
        DrawRectangleRec(zip.pole1,DARKGREEN);
        DrawRectangleRec(zip.pole2,DARKGREEN);
        if(zippy.overlapCheck(zip.pole1)){ 
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
                songs.setFading(true);
            }
        }

        if(zippy.overlapCheck({(curLevel.objective.getPoleTwo().x + curLevel.objective.getPoleOne().x)/2, (curLevel.objective.getPoleTwo().y + curLevel.objective.getPoleOne().y)/2, 50, 50})){
            currentMessage = loadingScreen;
            currentLevel = curLevel.objective.getConnectedLevel();
            drawState = true;
            StopSound(*songs.getCurSong());
            songs.nextSong();
            songs.setFading(false);
            zippy.spawn(currentLevel);
        }
    }
        
} 

/**
 * @brief moves the camera to keep the player centered
 * @param camera pointer to the camera
 * @param play pointer to the player
 */
void updateCam(Camera2D *camera, player *play){
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->target = (Vector2){ zippy.position.x,zippy.position.y };
}

/**
 * @brief Plays the current song
 * @param songs the AudioManager being used
 */
void updateAudio(AudioManager songs){
    Sound s = *songs.getCurSong();
        if(!IsSoundPlaying(s)){
            PlaySound(s); 
        }
    songs.Fade();
}

/**
 * @brief Runs the game
 */
int main () {
    if(TEST){
        currentLevelSet = &levelSetTest; 
    } else {
        currentLevelSet = &levelSet1; 
    }

    startingLevel = (*currentLevelSet)[2];
    currentLevel = startingLevel;

    zippy.spawn(currentLevel);

    cam.target = (Vector2){zippy.position.x,zippy.position.y};
    cam.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    cam.rotation = 0;
    cam.zoom = 1.0f;
    InitWindow(screenWidth,screenHeight, "Zipline Simulator");

    /*
    Load textures
    */

    pib = LoadTexture("textures/pibble.png"); 
    labDoor = LoadTexture("textures/door.png"); 
    obstacleTexture = LoadTexture("textures/danger.png"); 
    note = LoadTexture("textures/note.png");
    pointOfInterest = LoadTexture("textures/pointofinterest.png");
    playerTexture = LoadTexture("textures/player.png");
    playerZippingTexture = LoadTexture("textures/player_zipping.png");

    //connect doors and keys

    testLevel.doors[0].correspondingKey = &testLevel.keys[0];
    testLevel.keys[0].name = "Test Level Key";

    level3.doors[0].correspondingKey = &level3.keys[0];
    level3.keys[0].name = "First Door Key";
    level3.doors[1].correspondingKey = &level3.keys[1];
    level3.keys[1].name = "Second Door Key";
    level2.doors[0].correspondingKey = &level2.keys[0];
    level2.doors[3].correspondingKey = &level2.keys[0];
    level2.doors[4].correspondingKey = &level2.keys[0];
    level2.keys[0].name = "P.R.F Gate Key";
    level1.doors[0].correspondingKey = &level1.keys[0];
    level1.keys[0].name = "P.R.F Welcome Center key";
    level1.doors[1].correspondingKey = &level1.keys[1];
    level1.keys[1].name = "Backdoor key";
    level3.keys[0].name = "Key 1";
    level3.keys[1].name = "Key 2";
    level3.keys[2].name = "Key 3";
    level1.doors[0].correspondingKey = &level3.keys[2];
    level1.doors[1].correspondingKey = &level3.keys[2];
    level1.doors[2].correspondingKey = &level3.keys[2];
    level1.doors[3].correspondingKey = &level3.keys[1];
    level1.doors[4].correspondingKey = &level3.keys[1];
    level1.doors[5].correspondingKey = &level3.keys[0];
    level1.doors[6].correspondingKey = &level3.keys[0];
    //Introduction screen

    currentMessage = introductionMessage;
    drawState = true;

    SetTargetFPS(FPS);
    while (WindowShouldClose() == false){
        updateCam(&cam, &zippy);
        updateAudio(songs);
        BeginDrawing();
        ClearBackground({18, 32, 58, 255});
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
                        exit(0);
                    }
                }
            } else {
                BeginMode2D(cam);
                updateEnvironment(*currentLevel);
                zippy.Draw();
                if(!readState){
                    zippy.InputCheck();
                }
                zippy.Update();
                EndMode2D();

                if(toggleDrawInventory){
                    drawInventory();
                } else {
                    DrawText("Tab - Inventory", 50, 75, 25, WHITE);
                }
                if(readState){
                    zippy.setVelocity({0,0});
                    vector<string> linesOfText = currentMessage.wrapText();
                    currentMessage.renderReadMessage();
                    if (IsKeyPressed(KEY_E)){
                        currentMessage = defaultMessage;
                        readState = false;
                        readIndex = 0;
                    }
                    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && readIndex > 0){
                        readIndex--;
                    }
                    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && readIndex < (int)linesOfText.size() - 1){
                        readIndex++;
                    }
                    DrawRectangleRec((Rectangle){800, 400, 1050, 320}, GRAY);
                    DrawRectangleRec((Rectangle){820, 420, 1010, 280}, BLACK);
                    DrawText(linesOfText[readIndex].c_str(), 850, 540, 30, WHITE);
                    DrawText("E - Exit   A - Previous   D - Next", 880, 880, 25, WHITE);

                }
            }
        EndDrawing();
    }    
    songs.unloadAll();
    CloseWindow();
}

