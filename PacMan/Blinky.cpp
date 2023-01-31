#include "Blinky.h"

void Blinky::changeDirections() {
    if(isVulnerable()){
        nextDirection = chooseWorstDirection(pacmanXCoord, pacmanYCoord, xPos, yPos);
        return;
    }
    nextDirection = chooseBestDirection(pacmanXCoord, pacmanYCoord, xPos, yPos);
}

Blinky::Blinky(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent) : Ghost(xPos, yPos, imagePath, pacmanTimer, parent) {
    this->boxReleaseTimer = new QTimer();
    this->boxReleaseTimer->setInterval(BLINKY_RELEASE);
    this->boxReleaseTimer->setSingleShot(true);
    this->boxReleaseTimer->start();
    connect(boxReleaseTimer, SIGNAL(timeout()), SLOT(releaseFromBox()));
}