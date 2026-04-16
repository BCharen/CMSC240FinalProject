#include "level.h"

    Zipline::Zipline(){
        pole1 = {0,0,0,0};
        pole2 = {0,0,0,0};
    }

    Zipline::Zipline(Rectangle p1, Rectangle p2){
        pole1 = p1;
        pole2 = p2;
    }

    Vector2 Zipline::getZipStart(){
        Rectangle pole = pole1;
        return (Vector2){pole.x+(pole.width/2),pole.y};
    }

    Vector2 Zipline::getZipEnd(){
        Rectangle pole = pole2;
        return (Vector2){pole.x+(pole.width/2),pole.y};
    }

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

    LevelObjective::LevelObjective(Rectangle rec, level* toLevel){
        isPib = true;
        shape = rec;
        connectedLevel = toLevel;
    }

    LevelObjective::LevelObjective(Rectangle rec1, Rectangle rec2, level* toLevel){
        isPib = false;
        pole1 = rec1;
        pole2 = rec2;
        connectedLevel = toLevel;
    }

    level* LevelObjective::getConnectedLevel(){
        return connectedLevel;
    }

    bool LevelObjective::isThisPib(){
        return isPib;
    }

    Rectangle LevelObjective::getPibShape(){
        return shape;
    }

    Rectangle LevelObjective::getPoleOne(){
        return pole1;
    }

    Rectangle LevelObjective::getPoleTwo(){
        return pole2;
    }