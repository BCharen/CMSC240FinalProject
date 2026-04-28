#include "player.h"

/**
 * @brief collides the player with walls and floors/ceilings
 * @param otherRect The rectangle we are checking if we are collding with
 */
void player::collisionCheck(Rectangle otherRect){
    if(!CheckCollisionRecs(position,otherRect)){
        return;
    }

    //Need to rework collision check and repositioning, flawed for standing on moving non-dangerous obstacles

    if(otherRect.y+otherRect.height >= position.y && (otherRect.height+otherRect.y-position.y<=6) && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x)){
        VertColDir = UP;
        velocity.y = 0;
    }
    else if(otherRect.y <= position.y+position.height && (otherRect.x <= position.x+position.width || otherRect.x+otherRect.width >= position.x)){
        VertColDir = DOWN;
        isJumping = false;
        velocity.y = 0;
    }

    if(otherRect.x+otherRect.width >= position.x && (otherRect.width+otherRect.x-position.x<=6) && (otherRect.y <= position.y+position.height || otherRect.y+otherRect.height >= position.height)){
        HorColDir = LEFT;
        velocity.x = 0;
    }
    else if(otherRect.x <= position.x+position.width && (position.x+position.width-otherRect.x<=6) && (otherRect.y <= position.y+position.height || otherRect.y+otherRect.height >= position.height)){
        HorColDir = RIGHT;
        velocity.x = 0;
    }

}

/**
 * @brief Setter for player velocity
 * @param v new velocity
 */
void player::setVelocity(Vector2 v){
    velocity = v;
}


/**
 * @brief checks if the player is overlapping with another rectangle
 * @param otherRect the rectangle to check overlap with
 * @return whether or not the player is overlapping the other rectangle
 */
bool player::overlapCheck(Rectangle otherRect){
    return CheckCollisionRecs(position,otherRect);
}

/**
 * @brief checks if the players in on a ladder
 * @return the value of onLadder
 */
bool player::getOnLadder(){
    return onLadder;
}

/**
 * @brief sets the value of onLadder
 * @param val new state for onLadder
 */
void player::setOnLadder(bool val){
    if(isJumping) {
        onLadder = false;
        return;
    }
    onLadder = val;
}

/**
 * @brief handles all input for player movement
 */
void player::InputCheck(){
    if (VertColDir != NONE || HorColDir != NONE){
        wallJumped = false;
    }

    if (wallJumped){
        if (velocity.x > 0){
            if(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
                velocity.x = 1;
            }

            else if(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
                velocity.x = 5;
            }
        }

        if (velocity.x < 0){
            if(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
                velocity.x = -5;
            }

            else if(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
                velocity.x = -1;
            }
        }

        return;
    }

    if(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
        velocity.x = -5;
    }

    else if(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
        velocity.x = 5;
    } 

    else{
        velocity.x = 0;
    }

    if(onLadder){
        if
        ((IsKeyDown(KEY_W)||IsKeyDown(KEY_UP)) && VertColDir != UP) {velocity.y= -5;} 
        else if 
        ((IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN)) && VertColDir != DOWN){velocity.y = 5;} 
        else {velocity.y = 0;}
    } else if (IsKeyDown(KEY_SPACE) && (VertColDir == DOWN || onLadder)){
        if (HorColDir == LEFT){
            velocity.x = 3;
            wallJumped = true;
        } else if (HorColDir == RIGHT){
            velocity.x = -3;
            wallJumped = true;
        }
        velocity.y = -5;
    }
}

/**
 * @brief starts the player along a zipline
 * @param start the starting pole for the zipline
 * @param end the ending pole for the zipline
 */
void player::startZip(Rectangle start, Rectangle end){
    if (start.y <= end.y){
    position.x = start.x;
    position.y = start.y;
    zipVelocity = Vector2Normalize({end.x-start.x,end.y-start.y}) * 2;
    zipTarget = end;
    onZip = true;
    }
}

/**
 * @brief Updates the player's position
 */
void player::Update(){
    if(!onZip){
            if(!onLadder || wallJumped){
                //gravity setting
                velocity.y += gravity * GetFrameTime() * 3.5;
            }

            if(!((VertColDir == UP && velocity.y < 0)||(VertColDir == DOWN && velocity.y > 0))){
                    position.y+=velocity.y;
            } else {
                velocity.y = 0;
            }

            if(!((HorColDir == LEFT && velocity.x < 0)||(HorColDir == RIGHT && velocity.x > 0))){
                position.x+=velocity.x;
            }

        VertColDir = NONE;
        HorColDir = NONE;
    }
    else {
        //zipline max speed and acceleration rate, tune as nescessary to make it feel good
        if (Vector2Length(zipVelocity) < 180){
            zipVelocity += Vector2Normalize(Vector2Subtract({zipTarget.x, zipTarget.y}, {position.x, position.y})) * gravity * 4 * GetFrameTime();
        }
        position.x+=zipVelocity.x;
        position.y+=zipVelocity.y;
        if(CheckCollisionRecs(position,zipTarget)){
            onZip = false;
        }
}
}

/**
 * @brief Getter for if the player has won
 * @return the state of win
 */
bool player::checkWin(){
    return win;
}

/**
 * @brief Setter for the win state
 * @param isWin new value for the win state
 */
void player::changeWinState(bool isWin){
    win = isWin;
}

/**
 * @brief Getter for if the player has died
 * @return the state of dead
 */
bool player::isDead(){
    return dead;
}

/**
 * @brief Setter for dead state
 * @param isDead new value for dead state
 */
void player::changeDeadState(bool isDead){
    dead = isDead;
}

/**
 * @brief spawns the player in the level
 * @param lvl the current level to spawn into
 */
void player::spawn(level* lvl){
    onZip = false;
    zipVelocity = {0, 0};
    zipTarget = {0, 0};
    onLadder = false;
    wallJumped = false;
    position.x = (*lvl).spawnpoint.x;
    position.y = (*lvl).spawnpoint.y;
    velocity.x = 0;
    velocity.y = 0;
}