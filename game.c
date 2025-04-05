// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"


extern char *map, *dot_map;
extern int height;
extern int width;
//check if dots have been eaten by player
//repeated through array until all the dots are gone
int check_win(void) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; ++j) {
            if (dot_map[i * width + j] == DOT) {
                return KEEP_GOING;
                //printf("Dots remaining: %d\n", dot_map[i]);
            }
        }
    }
//if all not are gone then, YOU WIN!
        return YOU_WIN;

}

//checks if player has hit with a ghost
//updates after every position change
//if same ghost on player, return YOU LOSE
int check_loss(int player_y, int player_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < NUM_GHOSTS; ++i) {
        if (ghosts_y[i] == player_y && ghosts_x[i] == player_x) {
            //printf("Pacman hit ghost at (%d, %d)\n", ghosts_y[i], ghosts_x[i]);
            return YOU_LOSE;
            }
        }
        return KEEP_GOING;
    }

