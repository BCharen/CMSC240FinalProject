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

struct level {
    vector<Rectangle> walls;
    vector<key> keys;
    vector<door> doors;
    vector<Rectangle> ladders;
    vector<Rectangle> messages;
    vector<zipline> zips; 
};


#endif
