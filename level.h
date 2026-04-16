#ifndef level_h
#define level_h

#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;


struct hideableObject {
    Rectangle shape;
    bool show = true;

    hideableObject(Rectangle r) : shape(r) {}
};

struct key : hideableObject{
    using hideableObject::hideableObject;
};

struct door : hideableObject{
    key* correspondingKey = nullptr;

    using hideableObject::hideableObject;
};

struct zipline{
    Rectangle pole1;
    Rectangle pole2;
};

class Message{
    private:
    Rectangle shape;
    const char* text;
    Color color = {255,255,255,255};

    public:
    Message(float x, float y, const char* msg);

    Vector2 getCenteredPosition();

    void drawTextScreen();

    void drawTexture();

    Rectangle getShape();

    Color getColor();
};

struct level {
    vector<Rectangle> walls;
    vector<key> keys;
    vector<door> doors;
    vector<Rectangle> ladders;
    vector<Message> messages;
    vector<zipline> zips; 
    Vector2 spawnpoint;
    Rectangle objectiveCoordinates;
};

#endif