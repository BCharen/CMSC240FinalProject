#include "player.h"

void player::collisionCheck(Rectangle otherRect){
    if(!CheckCollisionRecs(position,otherRect)){
        return;
    }

    if(otherRect.y+otherRect.height >= position.y && (otherRect.height+otherRect.y-position.y<=10) && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x)){
        VertColDir = UP;
        }
    else if(otherRect.y <= position.y+position.height && (otherRect.x <= position.x+position.width || otherRect.x+otherRect.width >= position.x)){
        VertColDir = DOWN;
        }

    if(otherRect.x+otherRect.width >= position.x && (otherRect.width+otherRect.x-position.x<=10) && (otherRect.y <= position.y+position.height || otherRect.y+otherRect.height >= position.height)){
        HorColDir = LEFT;
        }
    else if(otherRect.x <= position.x+position.width && (otherRect.y <= position.y+position.height || otherRect.y+otherRect.height >= position.height)){
        HorColDir = RIGHT;
        }

    
        
}

void player::collide(Rectangle otherRect){
    
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
    if(IsKeyDown(KEY_W)) {velocity.y= -5;} else  {velocity.y = 5;} 
}