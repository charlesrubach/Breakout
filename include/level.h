#ifndef LEVEL_H
#define LEVEL_H

#include "brick.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Game Game;

#define LEVEL_STARTING_LEVEL  1

// Level definitions here
typedef struct Level {
    char *buffer;
    int levelNumber;
    int brickCount;
    int rows;
    int columns;
    int brick_width;
    int brick_height;
    Brick *bricks; // Pointer to an array of Bricks
} Level;

void LevelLoad(Game *game);
void LevelUpdate(Game *game);
void LevelRender(Game *game);
void LevelClear(Game *game);

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
