#pragma once

#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QWidget>
#include "Globals.h"

class Coin : public QGraphicsEllipseItem {
    private: 
        bool superCoin = false;
    public:
        Coin(int xCoord, int yCoord, bool isSuper);
        bool isSuper();
};