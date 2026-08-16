#ifndef LEVEL_H
#define LEVEL_H

#include "brick.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Game Game;

// Level definitions here
typedef struct Level {
    int levelNumber;
    int brickCount;
    int rows;
    int columns;
    int brick_width;
    int brick_height;
    Brick *bricks; // Pointer to an array of Bricks
} Level;

void LevelLoad(Game *game);
void LevelUpdate(Level *level);
void LevelRender(Level *level);
void LevelClear(Level *level);

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
