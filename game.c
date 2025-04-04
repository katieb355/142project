// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"


extern char *map, *dot_map;
extern int height;
extern int width;

int check_win(void) {
    for (int i = 0; i < height; i++) {
        //for (int j = 0; j < width; ++j) {
            if (dot_map[i] == DOT) {
                //return KEEP_GOING;
                //printf("Dots remaining: %d\n", dot_map[i]);
                return 0;
            }
        //}
    }

    return YOU_WIN;

}


int check_loss(int player_y, int player_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < NUM_GHOSTS; ++i) {
        if (ghosts_y[i] == player_y && ghosts_x[i] == player_x) {
            //printf("Pacman hit ghost at (%d, %d)\n", ghosts_y[i], ghosts_x[i]);
            return YOU_LOSE;

        }
    }
    return 0;
    //return KEEP_GOING;
}