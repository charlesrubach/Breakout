#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "game.h"

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool active; // Indicates if the ball is currently active in the game
    bool isLaunched; // Indicates if the ball has been launched from the paddle
} Ball;

void CreateBall(Game *game);
void UpdateBall(Ball *ball);
void DrawBall(Ball ball);

#endif
