#pragma once
#include "Globals.h"
#include "Ghost.h"

class Clyde : public Ghost {
    public:
    Clyde(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent = 0);
    private:
    void changeDirections() override;
};