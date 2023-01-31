#pragma once
#include "Globals.h"
#include "Ghost.h"

class Blinky : public Ghost {
    public:
    Blinky(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent = 0);
    private:
    void changeDirections() override;
};