#pragma once
#include "Globals.h"

#include <QGraphicsPixmapItem>
#include <QString>
#include <QObject>

class Life : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    public:
        Life(int lifeNumber, QString imagePath, QGraphicsItem* parent = 0);
    private:
        int posX;
        int posY;
        int livesLeft = 3;
        int lifeNumber;
    public slots:
        void updateLives();
};