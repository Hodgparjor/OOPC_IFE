#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QList>
#include <QColor>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QFontDatabase>
#include <QFont>

#include <string>

#include "Globals.h"
#include "MovingObject.h"
#include "Coin.h"
#include "Ghost.h"
#include "unistd.h"
class Pacman : public MovingObject, public QGraphicsPixmapItem{
    private:
        Q_OBJECT
        int speed = REGULAR_SPEED;
        void move(int currentDirection);
        void keyPressEvent(QKeyEvent *pressed);
        void detectCollisionWithObjects();
        QPixmap pacmanImg[4];
        QTimer* boostTimer;
        void finishDelay();
        void pacmanRevivalDelay();
        void handleCoinCollision(QGraphicsItem* object);
        void handleEnemyCollision(QGraphicsItem* object);
    public:
        Pacman(int xPos, int yPos, QGraphicsItem* parent = 0);
        QTimer* moveTimer;
    public slots:
        void makeMove();
        void offBoost();
        void finishGameWon();
        void finishGameLost();
    signals:
        void increaseScore(int score);
        void decreaseLives();
        void startBoost();
        void endBoost();
        void enemyEaten();
        void moved(int xPos, int yPos);
};