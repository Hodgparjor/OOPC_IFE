#pragma once
#include "Globals.h"

#include <QGraphicsPixmapItem>
#include <QString>

extern int MapTemplate[MAP_HEIGHT][MAP_WIDTH];

class Map : public QGraphicsPixmapItem, public QObject {
    public:
        Map(QString imagePath, QGraphicsItem *parent = 0);
};