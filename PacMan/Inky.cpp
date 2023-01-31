#include "Inky.h"

void Inky::changeDirections(){
    if(isVulnerable()){
        nextDirection = chooseWorstDirection(pacmanXCoord + CUT_OFF, pacmanYCoord + CUT_OFF, xPos, yPos);
        return;
    }
    nextDirection = chooseBestDirection(pacmanXCoord + CUT_OFF, pacmanYCoord + CUT_OFF, xPos, yPos);
}

Inky::Inky(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent) : Ghost(xPos, yPos, imagePath, pacmanTimer, parent) {
    this->boxReleaseTimer = new QTimer();
    this->boxReleaseTimer->setInterval(INKY_RELEASE);
    this->boxReleaseTimer->setSingleShot(true);
    this->boxReleaseTimer->start();
    connect(boxReleaseTimer, SIGNAL(timeout()), SLOT(releaseFromBox()));
}

