#include "Level.h"

Level::Level(){
        level = 1;
        ptsRequired = 50;
        movesMinus = 1;
        movesAllowed = 5 - movesMinus;
}

void Level::levelUp(){
        level++;
        int prePts = ptsRequired;
        ptsRequired*=3;
        movesAllowed=(ptsRequired-prePts)/10-(++movesMinus);
}

int Level::getLevel(){
        return level;
}
int Level::getPts(){
        return ptsRequired;
}
void Level::setPts(int p){
        ptsRequired = p;
}
int Level::getMovesAllowed(){
        return movesAllowed;
}
void Level::moveMade(){
        movesAllowed--;
}
