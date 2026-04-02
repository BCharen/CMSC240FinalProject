#include "player.h"

player::collisionCheck(int dir,Rect otherRect){
    if(!CheckCollisionRecs(position,otherRect)){
        return -1;
    }
    switch dir
    {
    case UP:  
        if(otherRect.y+otherRect.height <= position.y && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x));
        return UP;
    case LEFT:
        break;
    case DOWN:
        if(otherRect.y <= position.y+position.height && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x));
        return DOWN;
        break;
    case RIGHT:
        break;
    }
    default:
        return -1;
}