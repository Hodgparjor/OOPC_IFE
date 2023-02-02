#include "Ghost.h"

Ghost::Ghost(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    this -> xPos = xPos;
    this -> yPos = yPos;
    this -> xStart = xPos;
    this -> yStart = yPos;
    this-> imagePath = imagePath;
    setPixmap(QPixmap(imagePath).scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1));
    setPos(xStart * CELL_SIZE, yStart * CELL_SIZE);
    deathTimer = new QTimer();
    deathTimer->setInterval(DEATH_TIME);
    deathTimer->setSingleShot(true);
    connect(deathTimer, SIGNAL(timeout()), SLOT(releaseFromBox()));
    nextDirection = chooseRandomDirection();
    nextDirection = NONE;
    connect(pacmanTimer, SIGNAL(timeout()), this, SLOT(makeMove()));
}

vector<int> Ghost::possibleMoves(){
    vector<int> possibleMoves;
    for(int i =0; i <= 3; i++){
        if(isMovePossible(i)) {
            if((currentDirection + 2) % 4 != i){
                possibleMoves.push_back(i);
            }
        }
    }
    return possibleMoves;
}

int Ghost::chooseRandomDirection(){
    vector <int> directions = possibleMoves();
    srand(time(NULL));
    return directions[rand()%directions.size()];
}

void Ghost::move(int currentDirection){
    bool canChangeDirection = false;
    switch(currentDirection){
        case UP:
            moveBy(0, -speed);
            if(y() == (this->yPos - 1) * CELL_SIZE) {
                this->yPos--;
                canChangeDirection = true;
            }
            break;
        case RIGHT:
            moveBy(speed, 0);
            if(x() == (this->xPos + 1) * CELL_SIZE) {
                this->xPos++;
                canChangeDirection = true;
            }
            break;
        case DOWN:
            moveBy(0, speed);
            if(y() == (this->yPos + 1) * CELL_SIZE){ 
                this->yPos++;
                canChangeDirection = true;
            }
            break;
        case LEFT:
            moveBy(-speed, 0);
            if(x() == (this->xPos - 1) * CELL_SIZE){
                this->xPos--;
                canChangeDirection = true;
            }
            break;  
        default:
            break;
    }
    if (canChangeDirection) {
        changeDirections();
    }
}

void Ghost::makeMove(){
    if(vulnerable && isMovePossible(this->currentDirection)){
        move(this->currentDirection);
        if((int) x() % CELL_SIZE == 0 && (int) y() % CELL_SIZE == 0){
            this->currentDirection = chooseRandomDirection();
        }
        return;
    } else if(isMovePossible(this -> nextDirection) && (int) x() % CELL_SIZE == 0 && (int) y() % CELL_SIZE == 0){
        this->currentDirection = this->nextDirection;
        this->nextDirection = NONE;
    }
    if(isMovePossible(this->currentDirection)){
        move(this->currentDirection);
    }
}

void Ghost::makeVulnerable() {
    this->vulnerable = true;
    setPixmap(QPixmap("./assets/vulnerableghost.png").scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1));
}

void Ghost::makeRegular() {
    this->vulnerable = false;
    setPixmap(QPixmap(this->imagePath).scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1));
}

bool Ghost::isLive() {
    return this->live;
}

bool Ghost::isVulnerable() {
    return this->vulnerable;
}

void Ghost::moveToBox() {
    this->xPos = this->xStart;
    this->yPos = this->yStart;
    setPos(this->xPos * CELL_SIZE, this->yPos * CELL_SIZE);
    this->currentDirection = chooseRandomDirection();
    show();
}

void Ghost::releaseFromBox() {
    this->live = true;
    this->xPos = BOX_EXIT_X;
    this->yPos = BOX_EXIT_Y;
    setPos(this->xPos * CELL_SIZE, this->yPos * CELL_SIZE);
    this->currentDirection = chooseRandomDirection();
    show();
}

bool Ghost::directionFound(int currentDirection, vector<int> directions){
    return find(directions.begin(), directions.end(), currentDirection) != directions.end();
}

double Ghost::distance(int targetX, int targetY, int currentX, int currentY){
    return sqrt(pow(targetX - currentX, 2) + pow(targetY - currentY, 2));
}

void Ghost::updatePacmanPos(int pacmanXCoord, int pacmanYCoord){
    this->pacmanXCoord = pacmanXCoord;
    this->pacmanYCoord = pacmanYCoord;
}

void Ghost::startDeathtimer(){
    this->deathTimer -> start();
}

void Ghost::setVulnerable(bool status){
    this->vulnerable = status;
}

void Ghost::setAlive(bool status){
    this->live = status;
}

void Ghost::setNewDirection(int currentDirection){
    this->currentDirection = currentDirection;
}

int Ghost::getXCoord(){
    return this->xPos;
}

int Ghost::getYCoord(){
    return this->xPos;
}

int Ghost::chooseBestDirection(int targetX, int targetY, int currX, int currY){
    vector <int> directions = possibleMoves();
    double upDirectionDistance = MAX_DISTANCE;
    double downDirectionDistance = MAX_DISTANCE;
    double leftDirectionDistance = MAX_DISTANCE;
    double rightDirectionDistance = MAX_DISTANCE;
    if(directionFound(UP, directions)){
        upDirectionDistance = distance(targetX, targetY, currX, currY-1);

    }
    if(directionFound(LEFT, directions)){
        leftDirectionDistance = distance(targetX, targetY, currX - 1, currY);
        
    }
    if(directionFound(DOWN, directions)){
        downDirectionDistance = distance(targetX, targetY, currX, currY+1);
        
    }
    if(directionFound(RIGHT, directions)){
        rightDirectionDistance = distance(targetX, targetY, currX + 1, currY); 
    }
    return minDistanceDirection(upDirectionDistance, leftDirectionDistance, downDirectionDistance, rightDirectionDistance);
}

int Ghost::minDistanceDirection(double upDirectionDistance, double leftDirectionDistance, double downDirectionDistance, double rightDirectionDistance){
    double minDistance = min(upDirectionDistance, min(leftDirectionDistance, min(downDirectionDistance, rightDirectionDistance)));
    if (minDistance == upDirectionDistance) {
        return UP;
    } else if(leftDirectionDistance == minDistance){
        return LEFT;
    }
    else if(downDirectionDistance == minDistance){
        return DOWN;

    }else if(rightDirectionDistance == minDistance){
        return RIGHT;
    }
    return NONE;
}

int Ghost::chooseWorstDirection(int targetX, int targetY, int currX, int currY){
    vector <int> directions = possibleMoves();
    double upDirectionDistance = 0;
    double downDirectionDistance = 0;
    double leftDirectionDistance = 0;
    double rightDirectionDistance = 0;
    if(directionFound(UP, directions)){
        upDirectionDistance = distance(targetX, targetY, currX, currY-1);
    }
    if(directionFound(LEFT, directions)){
        leftDirectionDistance = distance(targetX, targetY, currX - 1, currY);

    }
    if(directionFound(DOWN, directions)){
        downDirectionDistance = distance(targetX, targetY, currX, currY+1);
        
    }
    if(directionFound(RIGHT, directions)){
        rightDirectionDistance = distance(targetX, targetY, currX + 1, currY); 
    }
    return maxDistanceDirection(upDirectionDistance, leftDirectionDistance, downDirectionDistance, rightDirectionDistance);
}

int Ghost::maxDistanceDirection(double upDirectionDistance, double leftDirectionDistance, double downDirectionDistance, double rightDirectionDistance){
    double maxDistance = max(upDirectionDistance, max(leftDirectionDistance, max(downDirectionDistance, rightDirectionDistance)));
    if (maxDistance == upDirectionDistance) {
        return UP;
    } else if(leftDirectionDistance == maxDistance){
        return LEFT;
    }
    else if(downDirectionDistance == maxDistance){
        return DOWN;

    }else if(rightDirectionDistance == maxDistance){
        return RIGHT;
    }
    return NONE;
}