#include "level.h"

#define FONTSIZE 20

    /**
     * @brief Initializes an obstacle which is a rectangle that moves between point sP and eP 
     * @param width the width of the obstacle
     * @param height the height of the obstacle
     * @param s the speed of the obstacle
     * @param sP starting point of the cycle
     * @param eP ending point of the cycle
     */
    Obstacle::Obstacle(float width, float height, int s, Vector2 sP, Vector2 eP){
        startPoint = sP;
        endPoint = eP;
        shape = {startPoint.x, startPoint.y, width, height};
        Vector2 dir = Vector2Normalize({eP.x - sP.x, eP.y - sP.y});
        speed = {dir.x * s / 10, dir.y * s / 10};
    };

    /**
     * @brief Initializes an obstacle which is a rectangle that moves between point sP and eP  
     * @param width the width of the obstacle
     * @param height the height of the obstacle
     * @param s the speed of the obstacle
     * @param sP starting point of the cycle
     * @param eP ending point of the cycle
     * @param danger bool determining whether or not the obstacle kills the player.
     */
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

    /**
     * @brief Function that moves the obstacle between the start and end point on its cycle.
     */
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

    /**
     * @brief Returns whether or not the obstacle will kill the player
     * @return The value of dangerous
     */
    bool Obstacle::isDangerous(){
        return dangerous;
    }

    /**
     * @brief default constructor for Zipline.
     */
    Zipline::Zipline(){
        pole1 = {0,0,0,0};
        pole2 = {0,0,0,0};
    }

    /** 
     * @brief Constructor that creates a zipline with two poles
     * @param p1 the rectangle defining the first pole of the zipline
     * @param p2 the rectangle defining the second pole of the zipline
     */
    Zipline::Zipline(Rectangle p1, Rectangle p2){
        pole1 = p1;
        pole2 = p2;
    }

    /**
     * @brief Getter for the position where the zipline attaches to the start pole.
     * @return the position where the zipline attaches to the start pole. 
     */
    Vector2 Zipline::getZipStart(){
        Rectangle pole = pole1;
        return (Vector2){pole.x+(pole.width/2),pole.y};
    }

    /**
     * @brief Getter for the position where the zipline attaches to the end pole.
     * @return the position where the zipline attaches to the end pole. 
     */
    Vector2 Zipline::getZipEnd(){
        Rectangle pole = pole2;
        return (Vector2){pole.x+(pole.width/2),pole.y};
    }

    /**
     * @brief Constructor for Messages
     * @param x x position for the in-level sprite
     * @param y y position for the in-level sprite
     * @param msg message to display
     * @param messageTexture the image of the note
     */
    Message::Message(float x, float y, const char* msg, Texture2D* messageTexture){
        note = messageTexture;
        shape = Rectangle{x, y, 20, 30};
        text = msg;
    }

    /**
     * @brief Getter for the position of a message
     * @return centered position of the message
     */
    Vector2 Message::getCenteredPosition(){
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 50, 2);
        Vector2 textDimensions{ (GetScreenWidth() - textSize.x) / 2.0f, (GetScreenHeight() - textSize.y) / 2.0f };
        return textDimensions;
    }

    /**
     * @brief Draws the text of a message at the listed position
     */
    void Message::drawTextScreen(){
        Vector2 position = getCenteredPosition();
        DrawText(text, position.x, position.y, 50, color);
    }

    /**
     * @brief Draws the note sprite in the level
     */
    void Message::drawTexture(){
        DrawTexturePro(*note, Rectangle{0, 0, 20, 30}, shape, (Vector2){0, 0}, 0,  WHITE);
    }

    /**
     *  @brief the note sprite while reading it.
     */
    void Message::renderReadMessage(){
        DrawTexturePro(*note, Rectangle{0, 0, 20, 30}, Rectangle{200, 150, shape.width * 25, shape.height * 25}, (Vector2){0, 0}, 0,  WHITE);
    }

    /**
     * @brief converts the message text into a vector of strings that fit in a textbox of width maxWidth 
     * @param maxWidth the width of the textBox
     * @return vector of separated strings
     */
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

    /**
     * @brief Getter for the location of the text
     * @return Returns the collision rectangle of the Message 
     */
    Rectangle Message::getShape(){
        return shape;
    }

    /**
     * @brief Getter for the texture of the note
     * @return returns the texture of the note
     */
    Texture2D Message::getNote(){
        return *note;
    }

    /**
     * @brief Constructor for a pib level objective
     * @param rec The collision box for the objective
     * @param toLevel the next level to visit
     */
    LevelObjective::LevelObjective(Rectangle rec, level* toLevel){
        isPib = true;
        shape = rec;
        connectedLevel = toLevel;
    }

    /**
     * @brief Constructor for a zipline level objective
     * @param rec1 The collision box for the first pole
     * @param rec2 The collision box for the second pole
     * @param toLevel the next level to visit
     */
    LevelObjective::LevelObjective(Rectangle rec1, Rectangle rec2, level* toLevel){
        isPib = false;
        pole1 = rec1;
        pole2 = rec2;
        connectedLevel = toLevel;
    }

    /**
     * @brief Gets the next level from an objective
     * @return the next level
     */
    level* LevelObjective::getConnectedLevel(){
        return connectedLevel;
    }

    /**
     * @brief function to check if an objective is the final goal
     * @return returns if an objective is the final goal
     */
    bool LevelObjective::isThisPib(){
        return isPib;
    }

    /**
     * @brief returns the shape of a final LevelObjective
     * @return returns the shape of a final LevelObjective
     */
    Rectangle LevelObjective::getPibShape(){
        return shape;
    }

    /**
     * @brief gets the first pole of a zipline objective
     * @return returns the shape of the first pole of a zipline objective 
     */
    Rectangle LevelObjective::getPoleOne(){
        return pole1;
    }

    /**
     * @brief gets the second pole of a zipline objective
     * @return returns the shape of the second pole of a zipline objective 
     */
    Rectangle LevelObjective::getPoleTwo(){
        return pole2;
    }