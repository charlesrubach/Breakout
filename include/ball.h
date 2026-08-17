#ifndef BALL_H
#define BALL_H

#include "raylib.h"

typedef struct Game Game;

typedef struct Ball {
    Vector2 center;
    Vector2 velocity;
    float speed;
    float radius;
    bool active; // Indicates if the ball is currently active in the game
    bool isLaunched; // Indicates if the ball has been launched from the paddle
    Color color;
} Ball;

void BallCreate(Game *game);
void BallUpdate(Game *game);
void BallRender(Game *game);
void BallDestroy(Game *game);

#endif
