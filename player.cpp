#include "player.h"

void player::collisionCheck(Rectangle otherRect){
    if(!CheckCollisionRecs(position,otherRect)){
        //velocity.y= 5;
        return;
    }

       
    if(otherRect.y+otherRect.height <= position.y && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x)){
        VertColDir = UP;
        velocity.y = 0;
        }
    else if(otherRect.y <= position.y+position.height && (otherRect.x <= position.x+position.width || otherRect.x+otherRect.width >= position.x)){
        velocity.y=0;
        VertColDir = DOWN;
        }

    /*case RIGHT:
        cout << "RIGHT" << endl;
        return true;
        */
        
}

void player::collide(Rectangle otherRect){
    
}

int player::lrInputCheck(){
    if(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
        return -5;
    }

    else if(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
        return 5;
    }
    else { 
        return 0;
    }
}