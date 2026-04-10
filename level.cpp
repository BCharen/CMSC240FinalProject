#ifndef level_h
#define level_h
#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;

struct hideableObject {
    Rectangle shape;
    bool show = true;
};

struct zipline{
    Rectangle pole1;
    Rectangle pole2;
};

struct level {
    vector<Rectangle> walls;
    vector<hideableObject> keys;
    vector<hideableObject> doors;
    vector<Rectangle> ladders;
    vector<Rectangle> messages;
    vector<zipline> zips; 
};


#endif
