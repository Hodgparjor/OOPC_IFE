#pragma once
#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFontDatabase>
#include <QString>

#include "Globals.h"

class ScoreCounter : public QGraphicsTextItem {
    private:
    Q_OBJECT
    int score;
    int coinsLeft;
    int livesLeft;
    void displayScore();

    public:
    ScoreCounter(int coinsLeft, int livesLeft);

    signals:
    void gameWon();
    void gameLost();
    
    public slots:
    void updateScore(int score);
    void updateLives();
};
