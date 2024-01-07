//
// Created by Vlad Puscaru on 29.12.2023.
//

#ifndef ARKANOID_CONSTANTS_H
#define ARKANOID_CONSTANTS_H

enum Scenes {
    MENU, PLAY
};

enum Entities {
    PLAYER, BALL, TILE
};

enum Actions {
    MOVE_LEFT, MOVE_RIGHT, SHOOT, ROTATE_LEFT, ROTATE_RIGHT,
    TOGGLE_COLLISIONS, QUIT
};

enum Fonts {
    MAIN_FONT = 0
};

struct ConfigPlayer {
    float bbWidth;
    float bbHeight;
    float speed;
};

struct ConfigBall {
    float bbWidth;
    float bbHeight;
    float speed;
};

struct ConfigTile {
    float bbWidth;
    float bbHeight;
    int lifespan;
};

#endif //ARKANOID_CONSTANTS_H
