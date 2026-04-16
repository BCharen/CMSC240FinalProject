#include "level.h"

    Message::Message(float x, float y, const char* msg){
        shape = Rectangle{x, y, 25, 25};
        text = msg;
    }

    Vector2 Message::getCenteredPosition(){
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 50, 2);
        Vector2 textDimensions{ (GetScreenWidth() - textSize.x) / 2.0f, (GetScreenHeight() - textSize.y) / 2.0f };
        return textDimensions;
    }

    void Message::drawTextScreen(){
        Vector2 position = getCenteredPosition();
        DrawText(text, position.x, position.y, 50, color);
    }

    void Message::drawTexture(){
        DrawRectangleRec(shape, color);
    }

    Rectangle Message::getShape(){
        return shape;
    }

    Color Message::getColor(){
        return color;
    }

