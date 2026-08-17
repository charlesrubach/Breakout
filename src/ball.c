#include "ball.h"
#include "game.h"
#include "paddle.h"
#include "raylib.h"


const float BALL_RADIUS = 8.0f;
const float BALL_INITIAL_SPEED = -100.0f;

static void BallSetPaddlePosition(Game *game);

void BallCreate(Game *game) {
  Ball *ball = game->ball;
  ball->radius = BALL_RADIUS;
  ball->velocity = (Vector2){0};
  ball->speed = BALL_INITIAL_SPEED;
  ball->active = true;
  ball->isLaunched = false;
  ball->color = GRAY;
  BallSetPaddlePosition(game);
}

void BallUpdate(Game *game) {
  Ball *ball = game->ball;
  Paddle *paddle = game->paddle;
  Brick *bricks = game->level->bricks;

  float dt = GetFrameTime(); // Get the time elapsed since the last frame
  if (ball->isLaunched) {
    ball->center.x += ball->velocity.x * dt;
    ball->center.y += ball->velocity.y * dt;
  } else {
    BallSetPaddlePosition(game);
    if (IsKeyPressed(KEY_SPACE)) {
      ball->isLaunched = true;
      ball->velocity.x = paddle->velocity * -1;
      ball->velocity.y = ball->speed;
    }
  }

  // Collision detection
  if (ball->center.x > game->screenWidth || ball->center.x < 0) {
    ball->velocity.x *= -1;
  }
  if (ball->center.y < 0 || ball->center.y > game->screenHeight) {
    ball->velocity.y *= -1;
  }

  // Check paddle collision
  if (CheckCollisionCircleRec(ball->center, ball->radius, paddle->rect)) {
    ball->velocity.x *= -1;
    ball->velocity.x += paddle->velocity;
    ball->velocity.y *= 1;
  }

  // Check brick collision
  for (int i = 0; i < game->level->brickCount; i++) {
    if (bricks[i].isActive) {
      if (CheckCollisionCircleRec(ball->center, ball->radius, bricks[i].rect)) {
        bricks[i].isActive = false;
        // ball->velocity.x *= -1;
        ball->velocity.y *= -1;
      }
    }
  }
}

void BallRender(Game *game) {
  Ball *ball = game->ball;
  DrawCircle(ball->center.x, ball->center.y, ball->radius, ball->color);
  DrawCircleLinesV(ball->center, ball->radius, BLACK);
}

// Private Functions
static void BallSetPaddlePosition(Game *game) {
  Ball *ball = game->ball;

  ball->center.x =
      game->paddle->rect.x + ((game->paddle->rect.width - ball->radius) / 2);
  ball->center.y = game->paddle->rect.y - ball->radius;
}