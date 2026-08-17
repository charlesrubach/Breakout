#include "game.h"
#include "config.h"
#include "level.h"
#include "paddle.h"
#include "ball.h"
#include "raylib.h"
#include "screens/logo.h"
#include "screens/title.h"
#include <stdio.h>
#include <stdlib.h>


void GameInit(Game *game) {
  game->state = SHOW_TITLE;
  game->screenWidth = SCREEN_WIDTH;
  game->screenHeight = SCREEN_HEIGHT;
  game->targetFPS = TARGET_FPS;

  LogoInit(game); // Initialize logo resources
  if (IsTextureValid(game->logo->texture)) {
    TraceLog(LOG_INFO, "Logo texture loaded successfully");
  } else {
    TraceLog(LOG_ERROR, "Failed to load logo texture");
    WindowShouldClose(); // Close the window if texture loading fails
  }

  TitleInit(game); // Initialize title resources

  // Initialize paddle
  game->paddle = (Paddle *)malloc(sizeof(Paddle));
  if (game->paddle == NULL) {
    fprintf(stderr, "Failed to allocate memory for Paddle struct\n");
    WindowShouldClose(); // Close the window if memory allocation fails
  } else {
    PaddleInit(game);
  }

  game->level = (Level *)malloc(sizeof(Level));
  if (game->level == NULL) {
    fprintf(stderr, "Failed to allocate memory for Level struct\n");
    WindowShouldClose();
  } else {
    game->level->levelNumber = LEVEL_STARTING_LEVEL;
    LevelLoad(game);
  }

  game->ball = (Ball *)malloc(sizeof(Ball));
  if(game->ball == NULL) {
    fprintf(stderr, "Failed to allocate memory for Ball struct\n");
    WindowShouldClose(); 
  } else {
    BallCreate(game);
  }
}

bool GameLoop(Game *game) {
  GameUpdate(game);
  GameRender(game);

  if (game->state == SHOW_ENDING) {
    return false; // Exit the loop if the game state is SHOW_ENDING
  } else {
    return true; // Continue the loop for other states
  }
}

void GameUpdate(Game *game) {
  switch (game->state) {
  case SHOW_LOGO:
    LogoUpdate(game);
    break;
  case SHOW_TITLE:
    // Update title screen logic here
    TitleUpdate(game);
    break;
  case SHOW_GAMEPLAY:
    // Update gameplay logic here
    PaddleUpdate(game);
    BallUpdate(game);
    LevelUpdate(game);
    break;
  case SHOW_ENDING:
    // Update ending screen logic here
    break;
  default:
    break;
  }
}

void GameRender(Game *game) {
  // Update
  //----------------------------------------------------------------------------------
  BeginDrawing();

  ClearBackground(RAYWHITE);

  switch (game->state) {
  case SHOW_LOGO:
    LogoRender(game);
    break;
  case SHOW_TITLE:
    TitleRender(game);
    break;
  case SHOW_GAMEPLAY:
    PaddleRender(game);
    BallRender(game);
    LevelRender(game);
    break;
  case SHOW_ENDING:
    // DrawText("ENDING SCREEN", 20, 20, 40, LIGHTGRAY);
    break;
  default:
    break;
  }

  EndDrawing();

  //----------------------------------------------------------------------------------
}
