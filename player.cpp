#include "player.h"

bool player::collisionCheck(int dir,Rectangle otherRect){
    if(!CheckCollisionRecs(position,otherRect)){
        velocity.y= 5;
        return false;
    }
    switch (dir)
    {
    /*case UP:
        cout << "UP" << endl;
        if(otherRect.y+otherRect.height <= position.y && (otherRect.x >= position.x+position.width || otherRect.x+otherRect.width <= position.x)){
        return true;
        }
    case LEFT:
        cout << "LEFT" << endl;
        return true;*/
    case DOWN:
        cout << "DOWN" << endl;
        if(otherRect.y <= position.y+position.height && (otherRect.x <= position.x+position.width || otherRect.x+otherRect.width >= position.x)){
            position.y = otherRect.y-position.height+1;
            velocity.y=0;
            return true;   
        }
    /*case RIGHT:
        cout << "RIGHT" << endl;
        return true;
        */
    default:
        cout << "DEFAULT" << endl;
        return false;
        break;
    }
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