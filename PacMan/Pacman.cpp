#include "Pacman.h"

Pacman::Pacman(int xPos, int yPos, QGraphicsItem* parent) : QGraphicsPixmapItem(parent){
    this -> xPos = xPos;
    this -> yPos = yPos;
    currentDirection = LEFT;
    nextDirection = NONE;
    pacmanImage[UP] = QPixmap("./assets/pacmanUp.png").scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1);
    pacmanImage[DOWN] = QPixmap("./assets/pacmanDown.png").scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1);
    pacmanImage[RIGHT] = QPixmap("./assets/pacmanRight.png").scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1);
    pacmanImage[LEFT] = QPixmap("./assets/pacmanLeft.png").scaled(CELL_SIZE * 1.1, CELL_SIZE * 1.1);
    setPixmap(pacmanImage[LEFT]);
    setPos(xPos * CELL_SIZE, yPos * CELL_SIZE);

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(makeAMove()));
    boostTimer =  new QTimer();
    boostTimer->setInterval(BOOST_TIME);
    boostTimer->setSingleShot(true);
    connect(boostTimer,SIGNAL(timeout()), SLOT(offBoost()));
    moveTimer->start(FRAMETIME);
}

void Pacman::keyPressEvent(QKeyEvent* pressed){
    switch (pressed -> key())
    {
        case Qt::Key_Up:
        case Qt::Key_W:
            this -> nextDirection = UP;
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            this -> nextDirection = LEFT;
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            this -> nextDirection = DOWN;
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            this -> nextDirection = RIGHT;
            break;
        case Qt::Key_Escape:
            QCoreApplication::quit();
        break;
    }
}

void Pacman::move(int currentDirection) {
    
    if(speed == BOOST_SPEED){
        if((int)x() % BOOST_SPEED == REGULAR_SPEED) moveBy(-REGULAR_SPEED, 0);
        if((int)y() % BOOST_SPEED == REGULAR_SPEED) moveBy(0, -REGULAR_SPEED);
    }
    switch(currentDirection){
        case UP:
            moveBy(0, -speed);
            if(y() == (this -> yPos - 1) * CELL_SIZE) {
                this -> yPos--;
                emit moved(xPos, yPos);
            }
            break;

        case RIGHT:
            moveBy(speed, 0);
            if(x() == (this -> xPos + 1) * CELL_SIZE) {
                this -> xPos++;
                emit moved(xPos, yPos);
            }
            break;

        case DOWN:
            moveBy(0, speed);
            if(y() == (this -> yPos + 1) * CELL_SIZE){ 
                this -> yPos++;
                emit moved(xPos, yPos);
            }
            break;

        case LEFT:
            moveBy(-speed, 0);
            if(x() == (this -> xPos - 1) * CELL_SIZE){
                this -> xPos--;
                emit moved(xPos, yPos);
            }
            break;
        
        default:
            break;
    }
}

void Pacman::makeAMove() {
    this -> determineCollisionWithObjects();
    if(isMovePossible(this -> nextDirection) && (int) x() % CELL_SIZE == 0 && (int) y()% CELL_SIZE == 0){
        this -> currentDirection = this -> nextDirection;
    }
    if(isMovePossible(this -> currentDirection)){
        setPixmap(QPixmap(pacmanImage[this->currentDirection]));
        move(this -> currentDirection);
    }
}

void Pacman::determineCollisionWithObjects() {
    QList<QGraphicsItem*> objects = collidingItems();
    for (auto object : objects){
        if(dynamic_cast<Coin*>(object) != nullptr){
            handleCoinCollision(object);
        } else if(dynamic_cast<Ghost*>(object) != nullptr){
            handleEnemyCollision(object);
        }
    }
}

void Pacman::offBoost() {
    this -> speed = REGULAR_SPEED;
    emit endBoost();
}

void Pacman::finishDelay()
{
    QTime time = QTime::currentTime().addSecs(EXIT_SCREEN_TIME);
    while (QTime::currentTime() < time){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Pacman::pacmanRevivalDelay()
{
    QTime time = QTime::currentTime().addSecs(REVIVAL_TIME);
    while (QTime::currentTime() < time){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Pacman::finishGameWon() {
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, this->scene()->width(), this->scene()->height());
    rect -> setBrush(QBrush(QColor(0, 0, 0)));
    this -> scene() -> addItem(rect);
    QGraphicsTextItem* win = new QGraphicsTextItem("VICTORY");
    int id = QFontDatabase::addApplicationFont("assets/Pixeboy-z8XGD.ttf");
    QFont font;
    font = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 100, 0);
    win->setFont(font);
    win->setDefaultTextColor(QColor(Qt::green));
    int x = (this->scene()->width() / 2) - (win->boundingRect().width() / 2);
    int y = (this->scene()->height() / 2) - (win->boundingRect().height() / 2);
    win->setPos(x, y);
    moveTimer->stop();
    this->scene()->addItem(win);
    finishDelay();
    QCoreApplication::quit();  
}

void Pacman::finishGameLost() {
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, this -> scene() -> width(), this -> scene() -> height());
    rect->setBrush(QBrush(QColor(0, 0, 0)));
    this->scene() -> addItem(rect);
    QGraphicsTextItem* loss = new QGraphicsTextItem("GAME OVER");
    int id = QFontDatabase::addApplicationFont("assets/Pixeboy-z8XGD.ttf");
    QFont font;
    font = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 90, 0);
    loss->setFont(font);
    loss->setDefaultTextColor(QColor(Qt::red));
    int x = (this->scene()->width() / 2) - (loss->boundingRect().width() / 2);
    int y = (this->scene()->height() / 2) - (loss->boundingRect().height() / 2);
    loss->setPos(x, y);
    moveTimer->stop();
    this->scene()->addItem(loss);
    finishDelay();
    QCoreApplication::quit(); 
}

void Pacman::handleCoinCollision(QGraphicsItem* object){
    Coin* newCoin = (Coin*) object;
    if(newCoin->isSuper()){
        this->scene()->removeItem(object);
        emit increaseScore(SPECIAL_COIN_POINTS);
        this->speed = BOOST_SPEED;
        emit startBoost();
        boostTimer->start();
    } else {
        this->scene()->removeItem(object);
        emit increaseScore(COIN_POINTS);
    }
}

void Pacman::handleEnemyCollision(QGraphicsItem* object){
    Ghost* newGhost = (Ghost*) object;
    if(newGhost->isLive()){
        if (this->speed == BOOST_SPEED){
            newGhost->setVulnerable(false);
            newGhost->setAlive(false);
            newGhost->hide();
            newGhost->startDeathtimer();
            newGhost->moveToBox();
            emit increaseScore(GHOST_POINTS);
        } else {
            emit decreaseLives();
            this->xPos = PACMAN_START_X;
            this->yPos = PACMAN_START_Y;
            this->currentDirection = LEFT;
            setPixmap(QPixmap(pacmanImage[LEFT]));
            setPos(xPos * CELL_SIZE, yPos * CELL_SIZE);
            pacmanRevivalDelay();
        }
    }
}