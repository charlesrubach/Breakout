#include "screens/title.h"
#include <stdio.h>
#include <stdlib.h>

static const float TITLE_FONT_SIZE_LARGE = 180.0f; // Font size for "Breakout"
static const float TITLE_FONT_SIZE_SMALL = 30.0f; // Font size for menu

static void UpdateTriangleForMenuItem(Game *game, Vector2 position, Vector2 textSize) {
  game->title->v1 = (Vector2){position.x - 5, position.y + textSize.y / 2 - 1};
  game->title->v2 = (Vector2){position.x - 5 - textSize.y / 2, position.y - 8 + (textSize.y / 2) - 1};
  game->title->v3 = (Vector2){position.x - 5 - textSize.y / 2, position.y + 8 + (textSize.y / 2) - 1};
}

void TitleInit(Game *game) {
  // Load title texture
  game->title = (Title *)malloc(sizeof(Title));
  if (game->title == NULL) {
    fprintf(stderr, "Failed to allocate memory for Title struct\n");
    return; // Handle memory allocation failure
  }

  Font font = GetFontDefault();
  float fontSize = TITLE_FONT_SIZE_LARGE;
  float breakoutY = (float)game->screenHeight / 4;
  float screenCenterX = (float)game->screenWidth / 2;
  float currentY = breakoutY;

  game->title->breakout.textSize = MeasureTextEx(font, "Breakout", fontSize, 1);
  game->title->breakout.position = (Vector2){screenCenterX - game->title->breakout.textSize.x / 2, currentY};

  fontSize = TITLE_FONT_SIZE_SMALL;
  currentY += game->title->breakout.textSize.y;

  game->title->start.textSize = MeasureTextEx(font, "Start", fontSize, 1);
  game->title->start.position = (Vector2){screenCenterX - game->title->start.textSize.x / 2, currentY};
  currentY += game->title->start.textSize.y;

  game->title->highScores.textSize = MeasureTextEx(font, "High Scores", fontSize, 1);
  game->title->highScores.position = (Vector2){screenCenterX - game->title->highScores.textSize.x / 2, currentY};
  currentY += game->title->highScores.textSize.y;

  game->title->options.textSize = MeasureTextEx(font, "Options", fontSize, 1);
  game->title->options.position = (Vector2){screenCenterX - game->title->options.textSize.x / 2, currentY};
  currentY += game->title->options.textSize.y;

  game->title->exit.textSize = MeasureTextEx(font, "Exit", fontSize, 1);
  game->title->exit.position = (Vector2){screenCenterX - game->title->exit.textSize.x / 2, currentY};

  game->title->state = TITLE_START; // Initialize title state
}

void TitleRender(Game *game) {
  // Render title screen elements here
  Font font = GetFontDefault();

  float fontSize = TITLE_FONT_SIZE_LARGE;
  float breakoutY = (float)game->screenHeight / 4;
  float screenCenterX = (float)game->screenWidth / 2;
  float currentY = breakoutY;

  // Draw "Breakout" text
  DrawTextEx(font, "Breakout", game->title->breakout.position, fontSize, 1, BLACK);

  fontSize = TITLE_FONT_SIZE_SMALL;
  currentY += game->title->breakout.textSize.y;

  // Draw "Start" text
  DrawTextEx(font, "Start", game->title->start.position, fontSize, 1, BLACK);
  currentY += game->title->start.textSize.y;

  // Draw "High Scores" text
  DrawTextEx(font, "High Scores", game->title->highScores.position, fontSize, 1, BLACK);
  currentY += game->title->highScores.textSize.y;

  // Draw "Options" text
  DrawTextEx(font, "Options", game->title->options.position, fontSize, 1, BLACK);
  currentY += game->title->options.textSize.y;

  // Draw "Exit" text
  DrawTextEx(font, "Exit", game->title->exit.position, fontSize, 1, BLACK);

  // Update triangle position based on current state
  Vector2 *menuPosition = NULL;
  Vector2 *menuSize = NULL;
  switch (game->title->state) {
    case TITLE_START:
      menuPosition = &game->title->start.position;
      menuSize = &game->title->start.textSize;
      break;
    case TITLE_HIGHSCORES:
      menuPosition = &game->title->highScores.position;
      menuSize = &game->title->highScores.textSize;
      break;
    case TITLE_OPTIONS:
      menuPosition = &game->title->options.position;
      menuSize = &game->title->options.textSize;
      break;
    case TITLE_EXIT:
      menuPosition = &game->title->exit.position;
      menuSize = &game->title->exit.textSize;
      break;
    default:
      break;
  }

  if (menuPosition && menuSize) {
    UpdateTriangleForMenuItem(game, *menuPosition, *menuSize);
    DrawTriangle(game->title->v1, game->title->v2, game->title->v3, BLACK);
  }
}

void TitleUnload(Game *game) { free(game->title); }

void TitleUpdate(Game *game) {
  // Update title screen logic here
  if (IsKeyPressed(KEY_DOWN)) {
    // Move cursor down
    game->title->state =
        (TitleState)((game->title->state + 1) %
                     TITLE_TOTAL_STATES); // Cycle through states
  }
  if (IsKeyPressed(KEY_UP)) {
    // Move cursor up
    game->title->state =
        (TitleState)((game->title->state - 1 + TITLE_TOTAL_STATES) %
                     TITLE_TOTAL_STATES); // Cycle through states
  }
  if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
    // Handle selection based on current state
    switch (game->title->state) {
      case TITLE_START:
        game->state = SHOW_GAMEPLAY; // Transition to gameplay
        break;
      case TITLE_HIGHSCORES:
        // Handle high scores logic here
        game->title->state = TITLE_HIGHSCORES; // Stay in high scores for now
        break;
      case TITLE_OPTIONS:
        // Handle options logic here
        game->title->state = TITLE_OPTIONS; // Stay in options for now
        break;
      case TITLE_EXIT:
        game->state = SHOW_ENDING; // Transition to ending
        break;
      default:
        break;
    }
  }
}