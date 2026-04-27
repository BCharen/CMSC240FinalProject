#include "level.h"

#define FONTSIZE 20
    Obstacle::Obstacle(float width, float height, int s, Vector2 sP, Vector2 eP){
        startPoint = sP;
        endPoint = eP;
        shape = {startPoint.x, startPoint.y, width, height};
        Vector2 dir = Vector2Normalize({eP.x - sP.x, eP.y - sP.y});
        speed = {dir.x * s / 10, dir.y * s / 10};
    };

    Obstacle::Obstacle(float width, float height, int s, Vector2 sP, Vector2 eP, bool danger){
        shape = {startPoint.x, startPoint.y, width, height};
        startPoint = sP;
        endPoint = eP;
        Vector2 distance = {eP.x - sP.x, eP.y - sP.y};
        if (Vector2Length(distance) == 0) {
            speed = {0, 0};
        } else {
            Vector2 dir = Vector2Normalize(distance);
            speed = {dir.x * s / 10, dir.y * s / 10};
        }
        dangerous = danger;
    };

    void Obstacle::obstacleUpdate() {
        shape.x += speed.x;
        shape.y += speed.y;

        if (shape.y < startPoint.y) {
            shape.x = startPoint.x;
            shape.y = startPoint.y;
            speed.x = -speed.x;
            speed.y = -speed.y;
        }
        else if (shape.y > endPoint.y) {
            shape.x = endPoint.x;
            shape.y = endPoint.y;
            speed.x = -speed.x;
            speed.y = -speed.y;
        }
    };

    bool Obstacle::isDangerous(){
        return dangerous;
    }

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

    Message::Message(float x, float y, const char* msg, Texture2D* messageTexture){
        note = messageTexture;
        shape = Rectangle{x, y, 20, 30};
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
        DrawTexturePro(*note, Rectangle{0, 0, 20, 30}, shape, (Vector2){0, 0}, 0,  WHITE);
    }

    void Message::renderReadMessage(){
        DrawTexturePro(*note, Rectangle{0, 0, 20, 30}, Rectangle{200, 150, shape.width * 25, shape.height * 25}, (Vector2){0, 0}, 0,  WHITE);
    }

    vector<string> Message::wrapText(float maxWidth) {
        vector<string> lines;

        string currentLine = "";
        string word = "";

        for (int i = 0; text[i] != '\0'; i++) {
            char c = text[i];

            if (c == ' ' || c == '\n') {
                string testLine = currentLine.empty() ? word : currentLine + " " + word;

                Vector2 size = MeasureTextEx(GetFontDefault(), testLine.c_str(), FONTSIZE, 2.0f);

                if (size.x > maxWidth) {
                    if (!currentLine.empty()) lines.push_back(currentLine);
                    currentLine = word;
                } else {
                    currentLine = testLine;
                }

                word = "";

                if (c == '\n') {
                    lines.push_back(currentLine);
                    currentLine = "";
                }
            } else {
                word += c;
            }
        }

        // last word
        if (!word.empty()) {
            string testLine = currentLine.empty() ? word : currentLine + " " + word;

            Vector2 size = MeasureTextEx(GetFontDefault(), testLine.c_str(), FONTSIZE, 2.0f);

            if (size.x > maxWidth) {
                if (!currentLine.empty()) lines.push_back(currentLine);
                lines.push_back(word);
            } else {
                currentLine = testLine;
            }
        }

        if (!currentLine.empty()) lines.push_back(currentLine);

        return lines;
    }


    Rectangle Message::getShape(){
        return shape;
    }

    Color Message::getColor(){
        return color;
    }

    Texture2D Message::getNote(){
        return *note;
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