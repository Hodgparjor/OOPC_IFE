#include "MovingObject.h"

bool MovingObject::isMovePossible(int currentDirection) {
    if (currentDirection == NONE) return false;
    switch (currentDirection) {
        case UP:
            if (MapTemplate[this -> yPos - 1][this ->xPos] == 1 ) return false;
            break;
        case LEFT:
            if (MapTemplate[this -> yPos][this ->xPos - 1] == 1) return false;
            break;
        case DOWN:
            if (MapTemplate[this -> yPos + 1][this ->xPos] == 1) return false;
            break;
        case RIGHT:
            if (MapTemplate[this -> yPos][this ->xPos + 1] == 1) return false;
            break;
        default:
            break;
    }
    return true;
}