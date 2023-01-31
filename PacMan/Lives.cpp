#include "Lives.h"
#include <iostream>
using namespace std;

Life::Life(int lifeNumber, QString imagePath, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    this->lifeNumber = lifeNumber;
    setPixmap(QPixmap(imagePath).scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1));
    switch(lifeNumber) {
        case 1:
            setPos(CELL_SIZE * (MAP_WIDTH - 2), CELL_SIZE * (MAP_HEIGHT - 2));
            break;
        case 2:
            setPos(CELL_SIZE * (MAP_WIDTH - 3), CELL_SIZE * (MAP_HEIGHT - 2));
            break;
        case 3:
            setPos(CELL_SIZE * (MAP_WIDTH - 4), CELL_SIZE * (MAP_HEIGHT - 2));
            break;
    }
}

void Life::updateLives() {
    this->livesLeft -= 1;
    if(this->livesLeft < this->lifeNumber) {
        delete this;
    }
}