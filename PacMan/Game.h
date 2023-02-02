#pragma once
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>

#include "Globals.h"
#include "Coin.h"
#include "Pacman.h"
#include "Map.h"
#include "Ghost.h"
#include "Clyde.h"
#include "Blinky.h"
#include "Inky.h"
#include "Pinky.h"
#include "Lives.h"
#include "ScoreAndLivesCounter.h"

using namespace std;

class Game : public QGraphicsView{
  Q_OBJECT
  public:
    Game(QWidget* parent = 0);
  private:
    QGraphicsScene * scene;
    Pacman* pacman;
    ScoreCounter* scoreCounter; 
    Ghost* ghosts[4];
    int generateMap();
    void addScoreCounter(int coinsLeft, int livesLeft);
    void addBlinky();
    void addInky();
    void addPinky();
    void addClyde();
    void drawMap();
    void addLives();
};
