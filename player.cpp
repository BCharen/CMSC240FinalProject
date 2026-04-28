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
    onLadder = val;
}

/**
 * 
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
    } else if (IsKeyDown(KEY_SPACE) && VertColDir == DOWN){
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

void player::startZip(Rectangle start, Rectangle end){
    if (start.y <= end.y){
    position.x = start.x;
    position.y = start.y;
    zipVelocity = Vector2Normalize({end.x-start.x,end.y-start.y}) * 2;
    zipTarget = end;
    onZip = true;
    }
}

bool player::checkWin(){
    return win;
}

void player::changeWinState(bool isWin){
    win = isWin;
}

bool player::isDead(){
    return dead;
}

void player::changeDeadState(bool isDead){
    dead = isDead;
}

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
