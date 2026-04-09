#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;

struct hideableObject {
    Rectangle shape;
    bool show = true;
};

struct level {
    vector<Rectangle> walls;
    vector<hideableObject> keys;
    vector<hideableObject> doors;
};



