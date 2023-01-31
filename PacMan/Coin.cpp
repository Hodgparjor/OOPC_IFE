#include "Coin.h"

Coin::Coin(int xPos, int yPos, bool isSuper){
    this->superCoin = isSuper;
    if (this->superCoin){
        setRect(0, 0, 2 * COIN_SIZE, 2 * COIN_SIZE);
        setPos(xPos * CELL_SIZE + MARGIN(2 * COIN_SIZE), yPos * CELL_SIZE+ MARGIN(2 * COIN_SIZE));
        QBrush brush;
        brush.setColor(Qt::white);
        brush.setStyle(Qt::SolidPattern);
    setBrush(brush);
    } else {
        setRect(0, 0, COIN_SIZE, COIN_SIZE);
        setPos(xPos * CELL_SIZE + MARGIN(COIN_SIZE), yPos * CELL_SIZE + MARGIN(COIN_SIZE));
        QBrush brush;
        brush.setColor(Qt::white);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);
    }
}

bool Coin::isSuper(){
    return this->superCoin;
}