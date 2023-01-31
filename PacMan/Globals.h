#pragma once
#include "limits.h"

#define CELL_SIZE 20
#define MAP_WIDTH 28
#define MAP_HEIGHT 34
#define COIN_SIZE (CELL_SIZE / 4)
#define MARGIN(size) ((CELL_SIZE - size) / 2)
#define REGULAR_SPEED 1
#define BOOST_SPEED 2* REGULAR_SPEED
#define FRAMETIME 10
#define BOOST_TIME 10000
#define DEATH_TIME 2000
#define COIN_POINTS 10
#define SPECIAL_COIN_POINTS 100
#define GHOST_POINTS 200
#define MAX_DISTANCE numeric_limits<double>::max();
#define CUT_OFF 5
#define EXIT_SCREEN_TIME 3
#define REVIVAL_TIME 1
#define PACMAN_START_X 14
#define PACMAN_START_Y 23
#define BOX_EXIT_X 14
#define BOX_EXIT_Y 11
#define BLINKY_RELEASE 3000
#define CLYDE_RELEASE 8000
#define PINKY_RELEASE 12000
#define INKY_RELEASE 16000

enum objects {
    PATH,
    WALL,
    POINT,
    SPECIAL_POINT,
    PACMAN
};

enum directions {
    UP,
    LEFT,
    DOWN,
    RIGHT,
    NONE
};
