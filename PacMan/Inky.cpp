#include "Inky.h"

void Inky::changeDirections(){
    int targetX = this->pacmanYPos;
    int targetY = this->pacmanYPos;
    switch(this->pacmanDirection) {
        case UP:
            targetX = this->pacmanXPos;
            targetY = this->pacmanYPos - CUT_OFF;
            break;
        case DOWN:
            targetX = this->pacmanXPos;
            targetY = this->pacmanYPos + CUT_OFF;
            break;
        case LEFT:
            targetX = this->pacmanXPos - CUT_OFF;
            targetY = this->pacmanYPos;
            break;
        case RIGHT:
            targetX = this->pacmanXPos + CUT_OFF;
            targetY = this->pacmanYPos;
            break;
    }
    if(isVulnerable()){
        nextDirection = chooseWorstDirection(targetX, targetY, xPos, yPos);
        return;
    }
    nextDirection = chooseBestDirection(targetX, targetY, xPos, yPos);
}

Inky::Inky(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent) : Ghost(xPos, yPos, imagePath, pacmanTimer, parent) {
    this->boxReleaseTimer = new QTimer();
    this->boxReleaseTimer->setInterval(INKY_RELEASE);
    this->boxReleaseTimer->setSingleShot(true);
    this->boxReleaseTimer->start();
    connect(boxReleaseTimer, SIGNAL(timeout()), SLOT(releaseFromBox()));
}

