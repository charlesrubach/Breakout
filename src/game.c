#include "raylib.h"
#include "game.h"
#include "screens/logo.h" 
#include "screens/title.h"
#include "config.h"

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
            DrawText("GAMEPLAY SCREEN", 20, 20, 40, LIGHTGRAY);
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
