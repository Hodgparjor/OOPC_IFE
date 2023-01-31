#include "ScoreAndLivesCounter.h"

void ScoreCounter::displayScore() {
    setPlainText("Score:" + QString::number(static_cast<int>(this->score)));
}

ScoreCounter::ScoreCounter(int coinsLeft, int livesLeft) {
    this->score = 0;
    this->coinsLeft = coinsLeft;
    this->livesLeft = livesLeft;
    int id = QFontDatabase::addApplicationFont("assets/Pixeboy-z8XGD.ttf");
    QFont font;
    font = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 36, 0);
    setFont(font);
    //setFont(QFont("Uroob", 30));
    setDefaultTextColor(Qt::white);
    setPos(0, CELL_SIZE * 31.5);
    displayScore();
}

void ScoreCounter::updateScore(int score) {
    this->score += score;
    if(score == COIN_POINTS || score == SPECIAL_COIN_POINTS){
        coinsLeft--;
    }
    if (coinsLeft == 0){
        emit gameWon();
    }
    displayScore();
}

void ScoreCounter::updateLives(){
    this -> livesLeft -= 1;
    if(livesLeft == 0){
        emit gameLost();
    }
    displayScore();
}