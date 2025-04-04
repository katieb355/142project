// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case GHOST:
            change_text_colour(PINK);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        case DOT:
            change_text_colour(WHITE);
            break;
        default:
            change_text_colour(WHITE);
    }

    printf("%c", c);
}



void print_map(void) {
    for (int i = 0; i < width + 2; i++) {
        printc(WALL);
        printf(" ");
    }
    printf("\n");
    for (int k = 0; k < height; k++) {
        printc(WALL);
        printf(" ");
        for (int j = 0; j < width; ++j) {
            printc(map[k * width + j]);
            printf(" ");
        }
        printc(WALL);
        printf("\n");
    }
    for (int i = 0; i < width + 2; ++i) {
        printc(WALL);
        printf(" ");
    }
    printf("\n");

    // printc(PLAYER);
}

int is_wall(int y, int x) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return YES_WALL;
    }
    if (map[y * width + x] == WALL) {
        return YES_WALL;
    }

    return NOT_WALL;
}

char *load_map(char *filename, int *map_height, int *map_width) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("The file was not found to read from\n");
        return NULL;
    }

    // First pass: calculate height and max width
    int width = 0, height = 0, current_width = 0;
    int c, col_counter = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            if (current_width > width) width = current_width;
            current_width = 0;
            col_counter = 0;
            height++;
        } else {
            if (col_counter % 3 == 0) {
                current_width++;
            }
            col_counter++;
        }
    }
    if (current_width > 0) height++;

    *map_width = width;
    *map_height = height;

    fclose(fp);
    fp = fopen(filename, "r");
    char *loaded_map = malloc(width * height);
    if (loaded_map == NULL) return NULL;

    int i = 0;
    col_counter = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            col_counter = 0;
            continue;
        }
        if (col_counter % 3 == 0) {
            switch (c) {
                case 'W':
                    loaded_map[i++] = WALL;
                    break;
                case 'G':
                    loaded_map[i++] = GHOST;
                    break;
                case 'P':
                    loaded_map[i++] = PLAYER;
                    break;
                case '.':
                    loaded_map[i++] = DOT;
                    break;
                default:
                    loaded_map[i++] = EMPTY;
                    break;
            }
        }
        col_counter++;
    }

    fclose(fp);
    return loaded_map;
}

void find_player(int *player_y, int *player_x) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == PLAYER) {
                *player_y = y;
                *player_x = x;
                return;
            }
        }
    }
}

void find_ghosts(int ghost_y[NUM_GHOSTS], int ghost_x[NUM_GHOSTS]) {
    int found = 0;
    for (int y = 0; y < height && found < NUM_GHOSTS; y++) {
        for (int x = 0; x < width && found < NUM_GHOSTS; x++) {
            if (map[y * width + x] == GHOST) {
                ghost_y[found] = y;
                ghost_x[found] = x;
                found++;
            }
        }
    }
}
