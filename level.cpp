#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;
struct level {
    vector<Rectangle> walls;
    vector<Rectangle> keys;
    vector<Rectangle> doors;
};
