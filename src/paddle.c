#include "paddle.h"
#include "config.h"

const float PADDLE_WIDTH = 100.0f;
const float PADDLE_HEIGHT = 20.0f;
const float PADDLE_ACCELERATION = 800.0f;
const float PADDLE_DECELERATION = 1200.0f;
const float PADDLE_Y_OFFSET =
    PADDLE_HEIGHT; // Distance from the bottom of the screen
const Color PADDLE_COLOR = BLUE;

void PaddleInit(Paddle *paddle) {
  paddle->rect.x = (float)(SCREEN_WIDTH - PADDLE_WIDTH) /
                   2; // Center the paddle horizontally
  paddle->rect.y = (float)(SCREEN_HEIGHT - PADDLE_HEIGHT -
                           PADDLE_Y_OFFSET); // Position the paddle
  paddle->rect.width = PADDLE_WIDTH;
  paddle->rect.height = PADDLE_HEIGHT;
  paddle->velocity = 0.0f;
  paddle->acceleration = PADDLE_ACCELERATION * PADDLE_WIDTH / paddle->rect.width;
  paddle->deceleration = PADDLE_DECELERATION * PADDLE_WIDTH / paddle->rect.width;
  paddle->direction = 0; // No movement initially
}

void PaddleUpdate(Paddle *paddle) {
  float dt = GetFrameTime(); // Get the time elapsed since the last frame

  if (IsKeyDown(KEY_LEFT)) {
    paddle->direction = -1; // Move left
  } else if (IsKeyDown(KEY_RIGHT)) {
    paddle->direction = 1; // Move right
  } else {
    paddle->direction = 0; // No movement
  }

  if (paddle->direction != 0) {
    // Accelerate while the key is held
    paddle->velocity += paddle->direction * paddle->acceleration * dt;
  } else {
    // Slow down naturally when no key is pressed
    if (paddle->velocity > 0.0f) {
      paddle->velocity -= paddle->deceleration * dt;
      if (paddle->velocity < 0.0f) {
        paddle->velocity = 0.0f;
      }
    } else if (paddle->velocity < 0.0f) {
      paddle->velocity += paddle->deceleration * dt;
      if (paddle->velocity > 0.0f) {
        paddle->velocity = 0.0f;
      }
    }
  }

  paddle->rect.x += paddle->velocity * dt;

  if (paddle->rect.x < 0) {
    paddle->rect.x = 0;   // Prevent moving off the left edge
    paddle->velocity = 0; // Stop movement
  } else if (paddle->rect.x + paddle->rect.width > SCREEN_WIDTH) {
    paddle->rect.x =
        SCREEN_WIDTH - paddle->rect.width; // Prevent moving off the right edge
    paddle->velocity = 0;                  // Stop movement
  }
}

void PaddleRender(Paddle *paddle) {
  DrawRectangleRec(paddle->rect, PADDLE_COLOR);
}