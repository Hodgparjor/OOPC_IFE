#include "Clyde.h"

void Clyde::changeDirections(){
    nextDirection = chooseRandomDirection();
}

Clyde::Clyde(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent) : Ghost(xPos, yPos, imagePath, pacmanTimer, parent) {
    this->boxReleaseTimer = new QTimer();
    this->boxReleaseTimer->setInterval(CLYDE_RELEASE);
    this->boxReleaseTimer->setSingleShot(true);
    this->boxReleaseTimer->start();
    connect(boxReleaseTimer, SIGNAL(timeout()), SLOT(releaseFromBox()));

}