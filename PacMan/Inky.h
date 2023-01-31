#include "Blinky.h"
#include "Ghost.h"

class Inky : public Ghost {
    public:
    Inky(int xPos, int yPos, QString imagePath, QTimer* pacmanTimer, QGraphicsItem *parent = 0);
    private:
    void changeDirections() override;
};
