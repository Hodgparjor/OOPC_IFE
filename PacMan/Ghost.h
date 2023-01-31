#pragma once

#include <QGraphicsPixmapItem>
#include <QString>
#include <QTimer>
#include "cmath"
#include <vector>
#include "MovingObject.h"
#include "Globals.h"

using namespace std;
class Ghost : public MovingObject, public QGraphicsPixmapItem {
    Q_OBJECT
    public:
        Ghost(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent = 0);
        bool isLive();
        bool isVulnerable();
        void startDeathtimer();
        void moveToBox();
        void setVulnerable(bool status);
        void setAlive(bool status);
        void setNewDirection(int currentDirection);
        int getXCoord();
        int getYCoord();
    private:
        bool live = true;
        int speed = REGULAR_SPEED;
        void move(int currentDirection);
        int minDistanceDirection(double upDirectionDistance, double leftDirectionDistance, double downDirectionDistance, double rightDirectionDistance);
        int maxDistanceDirection(double upDirectionDistance, double leftDirectionDistance, double downDirectionDistance, double rightDirectionDistance);
        bool vulnerable = false;
    protected:
        QString imagePath;
        QTimer* deathTimer;
        QTimer* boxReleaseTimer;
        int xStart;
        int yStart; 
        int chooseBestDirection(int targetX, int targetY, int currX, int currY);
        int chooseWorstDirection(int targetX, int targetY, int currX, int currY);
        int chooseRandomDirection();
        int pacmanXCoord = PACMAN_START_X;
        int pacmanYCoord = PACMAN_START_Y;
        int initialBoxReleaseTime = DEATH_TIME;
        virtual void changeDirections() = 0;
        vector <int> possibleMoves();
        double distance(int targetX, int targetY, int currentX, int currentY);
        bool directionFound(int currentDirection, vector<int> directions);
    public slots:
        void makeVulnerable();
        void makeRegular();
        void makeAMove();
        void releaseFromBox();
        void updatePacmanCoords(int pacmanXCoord, int pacmanYCoord);
};