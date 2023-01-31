#pragma once
#include "Ghost.h"
#include "Globals.h"

class Pinky : public Ghost {
    public:
    Pinky(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent = 0);
    private:
    void changeDirections() override;
};


