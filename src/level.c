#define _POSIX_C_SOURCE 200112L
#include "level.h"
#include "cJSON.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <errno.h>
#endif

const char *json_file = "resources/breakout_levels.json";

static char *ReadLevelFile(const char *filename);
static int GetLevel(Game *game, const char *const breakout_levels);

void LoadLevel(Game *game) {
  // Load breakout_levels.json

  char *buffer = ReadLevelFile(json_file);

  if (buffer == NULL) {
    fprintf(stderr, "Unable to read the JSON file\n");
    return;
  }

  GetLevel(game, buffer);

  free(buffer);
}

// Read in the file and return a pointer to the buffer
static char *ReadLevelFile(const char *filename) {
  FILE *file_ptr = NULL;
  char *buffer;
  long numbytes;

  // Open the file and make sure it exists
#ifdef _WIN32
  errno_t err = fopen_s(&file_ptr, filename, "r");
#else
  file_ptr = fopen(filename, "r");
  int err = (file_ptr == NULL) ? errno : 0;
#endif

  if (err != 0) {
    // If an error occurred, file_ptr is guaranteed to be NULL
    char err_msg[80];

#ifdef _WIN32
    strerror_s(err_msg, sizeof(err_msg), err);
#else
    strerror_r(err, err_msg, sizeof(err_msg));
#endif

    fprintf(stderr, "Error opening file: %s (Error code: %d)\n", err_msg, err);
    return NULL;
  }

  // Get the number of bytes
  fseek(file_ptr, 0L, SEEK_END);
  numbytes = ftell(file_ptr);

  // Reset the file position indicator to the beginning of the file
  fseek(file_ptr, 0L, SEEK_SET);

  // Grab sufficient memory for the buffer to hld the text
  buffer = (char *)calloc(numbytes, sizeof(char));

  if (buffer == NULL) {
    return NULL;
  }

  // Copy all the text into the buffer
  fread(buffer, sizeof(char), numbytes, file_ptr);

  // Confirm we have read the file by outputing it to the console
  //   printf("The file contains this text\n\n%s", buffer);

  // Always close the file pointer when finished
  fclose(file_ptr);

  return buffer;
}

static int GetLevel(Game *game, const char *const breakout_levels) {
  const cJSON *level;
  const cJSON *levels;
  const cJSON *bricks;
  const cJSON *brick;
  int levelCount;
  int brickCount;
  int index = 0;

  int status = 0;
  cJSON *root = cJSON_Parse(breakout_levels);
  if (root == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    status = 0;
    goto end;
  }

  // Get "levels" array
  levels = cJSON_GetObjectItemCaseSensitive(root, "levels");
  levelCount = cJSON_GetArraySize(levels);

  // Find "Level 1"
  cJSON_ArrayForEach(levels, levels) {
    level = cJSON_GetObjectItemCaseSensitive(levels, "level");

    if (cJSON_IsString(level) && (level->valuestring != NULL)) {
      if (atoi(level->valuestring) == game->level->levelNumber) {
        printf("Level found!\n");
        goto bricks;
      }
    }
    index++;
  }

bricks:
//   bricks = cJSON_GetObjectItemCaseSensitive(level, "bricks");
  bricks = cJSON_GetArrayItem(levels, index);
  brickCount = cJSON_GetArraySize(bricks);

  // Get all bricks
  cJSON_ArrayForEach(bricks, bricks) {
    cJSON *row;
    cJSON *col;
    cJSON *color;

    brick = cJSON_GetArrayItem(bricks, 0);

    row = cJSON_GetObjectItemCaseSensitive(brick, "row");
    col = cJSON_GetObjectItemCaseSensitive(brick, "col");
    color = cJSON_GetObjectItemCaseSensitive(brick, "color");

    printf("row %d, col %d, color %s\n", row->valueint, col->valueint, color->valuestring);


  }


end:
  cJSON_Delete(root);

  return status;
}