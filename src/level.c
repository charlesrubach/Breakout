#include "level.h"
// #include "cJSON.h"
#include <stdio.h>
#include <string.h>

const char *filename ="resources/breakout_levels.json";

void LoadLevel(Level *level, int levelNumber) {
    // Load breakout_levels.json
    FILE* file_ptr = NULL;

    errno_t err = fopen_s(&file_ptr, filename, "r");

    if(err != 0) {
        // If an error occurred, file_ptr is guaranteed to be NULL
        char err_msg[80];
        strerror_s(err_msg, sizeof(err_msg), err);
        fprintf(stderr, "Error opening file: %s (Error code: %d)\n", err_msg, err);
        return;
    }


     // Read and print file contents
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
        printf("%s", buffer);
    }

    // Always close the file pointer when finished
    fclose(file_ptr);
}