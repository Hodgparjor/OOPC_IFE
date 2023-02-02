#include <iostream>
#include "Game.h"

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
	scene = new QGraphicsScene();
	setSceneRect(0, 0, MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE);
	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(CELL_SIZE * MAP_WIDTH, CELL_SIZE * MAP_HEIGHT);
	scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
	drawMap();
	int coinsLeft = generateMap();
	int livesLeft = 3;

	addScoreCounter(coinsLeft, livesLeft);

	addBlinky();
	addClyde();
	addInky();
	addPinky();
	addLives();
}

int Game::generateMap(){
	int coinsLeft = 0;
	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			if(MapTemplate[y][x] == SPECIAL_POINT) {
				scene -> addItem(new Coin(x, y, true));
				coinsLeft++;
			}
			if(MapTemplate[y][x] == POINT) {
				scene -> addItem(new Coin(x, y, false));
				coinsLeft++;
			}
			if(MapTemplate[y][x] == PACMAN) {
				pacman = new Pacman(x, y);
				pacman -> setFlag(QGraphicsItem::ItemIsFocusable);
				pacman -> setFocus();
				scene -> addItem(pacman);
			}
		}
	}
	return coinsLeft;
}

void Game::addScoreCounter(int coinsLeft, int livesLeft){
	scoreCounter = new ScoreCounter(coinsLeft, livesLeft);
	scene -> addItem(scoreCounter);
	connect(pacman, SIGNAL(increaseScore(int)), scoreCounter, SLOT(updateScore(int)));
	connect(pacman, SIGNAL(decreaseLives()), scoreCounter, SLOT(updateLives()));
	connect(scoreCounter, SIGNAL(gameWon()), pacman, SLOT(finishGameWon()));
	connect(scoreCounter, SIGNAL(gameLost()), pacman, SLOT(finishGameLost()));
}

void Game::addBlinky(){
	ghosts[0] = new Blinky(12, 14, "./assets/redghost.png", pacman->moveTimer);
	scene -> addItem(ghosts[0]);
	connect(pacman, SIGNAL(startBoost()), ghosts[0], SLOT(makeVulnerable()));
	connect(pacman, SIGNAL(endBoost()), ghosts[0], SLOT(makeRegular()));
	connect(pacman, SIGNAL(moved(int, int)), ghosts[0], SLOT(updatePacmanPos(int, int)));
	ghosts[0] -> setNewDirection(UP);
}

void Game::addClyde(){
	ghosts[1] = new Clyde(13, 14, "./assets/orangeghost.png", pacman -> moveTimer);
	scene -> addItem(ghosts[1]);
	connect(pacman, SIGNAL(startBoost()), ghosts[1], SLOT(makeVulnerable()));
	connect(pacman, SIGNAL(endBoost()), ghosts[1], SLOT(makeRegular()));
	ghosts[1] -> setNewDirection(LEFT);
}

void Game::addInky(){
	ghosts[2] = new Inky(14, 14, "./assets/blueghost.png", pacman -> moveTimer);
	scene -> addItem(ghosts[2]);
	connect(pacman, SIGNAL(startBoost()), ghosts[2], SLOT(makeVulnerable()));
	connect(pacman, SIGNAL(endBoost()), ghosts[2], SLOT(makeRegular()));
	connect(pacman, SIGNAL(moved(int, int)), ghosts[2], SLOT(updatePacmanPos(int, int)));
	connect(pacman, SIGNAL(directionChanged(int)), ghosts[2], SLOT(updatePacmanDirection(int)));
	ghosts[2] -> setNewDirection(RIGHT);
}

void Game::drawMap() {
	Map* map = new Map("./assets/map.png");
	scene->addItem(map);
}

void Game::addPinky(){
	Pinky* pinky = new Pinky(14, 13, "./assets/pinkghost.png", pacman -> moveTimer);
	ghosts[3] = pinky;
	scene -> addItem(ghosts[3]);
	connect(pacman, SIGNAL(startBoost()), ghosts[3], SLOT(makeVulnerable()));
	connect(pacman, SIGNAL(endBoost()), ghosts[3], SLOT(makeRegular()));
	connect(pacman, SIGNAL(directionChanged(int)), ghosts[3], SLOT(updatePacmanDirection(int)));
	ghosts[3] -> setNewDirection(DOWN);
}

void Game::addLives() {
	Life* life1 = new Life(1, "assets/pacmanLeft.png");
	Life* life2 = new Life(2, "assets/pacmanLeft.png");
	Life* life3 = new Life(3, "assets/pacmanLeft.png");
	scene->addItem(life1);
	scene->addItem(life2);
	scene->addItem(life3);
	connect(pacman, SIGNAL(decreaseLives()), life1, SLOT(updateLives()));
	connect(pacman, SIGNAL(decreaseLives()), life2, SLOT(updateLives()));
	connect(pacman, SIGNAL(decreaseLives()), life3, SLOT(updateLives()));
}