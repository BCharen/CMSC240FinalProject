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

class Message{
    private:
    Rectangle shape;
    const char* text;
    Color color = {255,255,255,255};

    public:
    Message(float x, float y, const char* msg){
        shape = Rectangle{x, y, 25, 25};
        text = msg;
    }

    Vector2 getCenteredPosition(){
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 50, 2);
        Vector2 textDimensions{ (GetScreenWidth() - textSize.x) / 2.0f, (GetScreenHeight() - textSize.y) / 2.0f };
        return textDimensions;
    }

    void drawTextScreen(){
        Vector2 position = getCenteredPosition();
        DrawText(text, position.x, position.y, 50, color);
    }

    void drawTexture(){
        DrawRectangleRec(shape, color);
    }

    Rectangle getShape(){
        return shape;
    }

    Color getColor(){
        return color;
    }
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
    vector<Message> messages;
    vector<zipline> zips; 
};


#endif
