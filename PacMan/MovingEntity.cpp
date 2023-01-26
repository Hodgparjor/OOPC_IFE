#include "Map.h"
#include "MovingEntity.h"

MovingEntity::Direction::Direction(int newDirection) {
    switch (newDirection) {
        case UP:
            this->x = 0;
            this->y = -1;
            break;
        case DOWN:
            this->x = 0;
            this->y = 1;
            break;
        case LEFT:
            this->x = -1;
            this->y = 0;
            break;
        case RIGHT:
            this->x = 1;
            this->y = 0;
            break;
        case NONE:
            this->x = 0;
            this->y = 0;
    }
}

void MovingEntity::changeDirection(int newDirection) {}



