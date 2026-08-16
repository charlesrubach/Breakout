#ifndef BRICK_H
#define BRICK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "raylib.h"

#define BRICK_COLUMNS    8
#define BRICK_ROWS      6

typedef struct Brick {
    Vector2 pos;
    Color color;
    int health; // Number of hits the block can take before being destroyed
    int points; // Points awarded for destroying the block
    bool isActive; // Indicates if the block is still active (not destroyed)
} Brick;

#ifdef __cplusplus
}
#endif

#endif // BRICK_H
