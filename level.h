#ifndef level_h
#define level_h

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>
using namespace std;

struct level;

struct hideableObject {
    Rectangle shape;
    bool show = true;

    hideableObject() : shape({0,0,0,0}) {};
    hideableObject(Rectangle r) : shape(r) {};
    void setShow(bool s){show = s;};
};

struct key : hideableObject{
    string name = "key";
    using hideableObject::hideableObject;
};

struct door : hideableObject{
    key* correspondingKey = nullptr;

    using hideableObject::hideableObject;
};

class Obstacle : public hideableObject{
    private:
    Vector2 speed;
    Vector2 startPoint;
    Vector2 endPoint; 
    bool dangerous = true;

    public:
    Obstacle(float width, float height, int s, Vector2 sP, Vector2 eP);
    Obstacle(float width, float height, int s, Vector2 sP, Vector2 eP, bool danger);

    void obstacleUpdate();
    bool isDangerous();
};

class Zipline{
    public:
    Rectangle pole1;
    Rectangle pole2;

    Zipline();

    Zipline(Rectangle p1, Rectangle p2);

    Vector2 getZipStart();

    Vector2 getZipEnd();
};

class Message{
    private:
    Rectangle shape;
    Texture2D* note;
    const char* text;
    Color color = {255,255,255,255};

    public:
    Message(float x, float y, const char* msg, Texture2D* messageTexture);

    Vector2 getCenteredPosition();

    void drawTextScreen();

    void drawTexture();

    void renderReadMessage();

    Rectangle getShape();

    Color getColor();

    Texture2D getNote();
};

class LevelObjective : public Zipline{
    private:
    Rectangle shape;
    bool isPib;
    level* connectedLevel;

    public:

    LevelObjective(Rectangle rec, level* toLevel);

    LevelObjective(Rectangle rec1, Rectangle rec2, level* toLevel);

    level* getConnectedLevel();

    bool isThisPib();

    Rectangle getPibShape();

    Rectangle getPoleOne();

    Rectangle getPoleTwo();
};

struct level {
    vector<Rectangle> walls;
    vector<key> keys;
    vector<door> doors;
    vector<Rectangle> ladders;
    vector<Message> messages;
    vector<Zipline> zips; 
    vector<Obstacle> obstacles;
    Vector2 spawnpoint;
    LevelObjective objective;
};

#endif