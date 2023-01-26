

struct MovingEntity::Direction {
    int x;
    int y;
    Direction(int newDirection = NONE);
};

class MovingEntity {
    private:
        int xPos;
        int yPos;
        int speed;
    public:
        struct Direction;
        Direction nextDirection;
        void changeDirection(int newDirection);
};

enum directions {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

