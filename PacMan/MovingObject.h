#pragma once
#include "Globals.h"
#include "Map.h"
#include <QObject>

class MovingObject : public QObject {
    
    Q_OBJECT
    protected:
    int xPos;
    int yPos;
    int currentDirection = LEFT;
    int nextDirection = NONE;
    bool isMovePossible(int currentDirection);
    virtual void move(int currentDirection) = 0;
    public slots:
    virtual void makeAMove() = 0;
};
