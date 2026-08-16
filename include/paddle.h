#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

typedef struct Paddle {
    Rectangle rect;
    float velocity;
    float acceleration; // Acceleration for smoother movement
    float deceleration; // Deceleration for smoother stopping
    float direction; // -1 for left, 1 for right, 0 for no movement
    Color color;
} Paddle;

void PaddleInit(Paddle *paddle);
void PaddleUpdate(Paddle *paddle);
void PaddleRender(Paddle *paddle);

#endif
