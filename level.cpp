#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;
struct level {
    vector<Rectangle> floors;
    vector<Rectangle> walls;
    vector<Rectangle> ceils;
    vector<Rectangle> keys;
    vector<Rectangle> doors;
};
