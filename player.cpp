#include "player.h"

void player::collisionCheck(Rectangle otherRect){
    if(!CheckCollisionRecs(position,otherRect)){
        return;
    }

    if(otherRect.y+otherRect.height >= position.y && (otherRect.height+otherRect.y-position.y<=10) && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x)){
        VertColDir = UP;
    }
    else if(otherRect.y <= position.y+position.height && (otherRect.x <= position.x+position.width || otherRect.x+otherRect.width >= position.x)){
        if(!onLadder) {VertColDir = DOWN; }
        }

    if(otherRect.x+otherRect.width >= position.x && (otherRect.width+otherRect.x-position.x<=10) && (otherRect.y <= position.y+position.height || otherRect.y+otherRect.height >= position.height)){
        HorColDir = LEFT;
        }
    else if(otherRect.x <= position.x+position.width && (position.x+position.width-otherRect.x<=10) && (otherRect.y <= position.y+position.height || otherRect.y+otherRect.height >= position.height)){
        HorColDir = RIGHT;
        }

}

bool player::keyCheck(Rectangle otherRect){
    return !CheckCollisionRecs(position,otherRect);
}

bool player::overlapCheck(Rectangle otherRect){
    return CheckCollisionRecs(position,otherRect);
}

bool player::getOnLadder(){
    return onLadder;
}

void player::setOnLadder(bool val){
    onLadder = val;
}
void player::lrInputCheck(){
    if(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
        velocity.x = -5;
    }

    else if(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
        velocity.x = 5;
    }

    else {
        velocity.x =  0;
    }

    if(onLadder){
        if(IsKeyDown(KEY_W)||IsKeyDown(KEY_UP)) {velocity.y= -5;} else if (IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN)){velocity.y = 5;} else { velocity.y = 0;}
    }
    else{
        velocity.y=5;
    }
}

void player::startZip(Vector2 start, Vector2 end){
    if (start.y <= end.y){
    position.x = start.x;
    position.y = start.y;
    zipVelocity = {(end.x-start.x)/100,(end.y-start.y)/100};
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