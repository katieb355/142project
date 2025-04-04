// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "actor.h"
#include "map.h"
extern int width;
extern int height;
extern char *map;
extern char *dot_map;


char sees_player(int player_y, int player_x, int ghost_y, int ghost_x){
    if (ghost_x==player_x&&ghost_y==player_y){
        return EATING_PLAYER;
    }
    if (ghost_x != player_x&&ghost_y!=player_y){
        return SEES_NOTHING;
    }

    if (player_x == ghost_x) {
        int step = (player_y > ghost_y) ? 1 : -1;
        for (int y = ghost_y + step; y != player_y; y += step) {
            if (map[y * width + ghost_x] == WALL) {
                return SEES_NOTHING;
            }
        }
        return (step == 1) ? DOWN : UP;

    }
    if (player_y == ghost_y) {
        int step = (player_x > ghost_x) ? 1 : -1;
        for (int x = ghost_x + step; x != player_x; x += step) {
            if (map[ghost_y * width + x] == WALL) {
                return SEES_NOTHING;
            }
        }
        return (step == 1) ? RIGHT : LEFT;
    }
    return SEES_NOTHING;
}

int move_player(int *player_y, int *player_x, char direction) {
    int new_y = *player_y;
    int new_x = *player_x;
    if (direction != LEFT && direction != RIGHT && direction != UP && direction != DOWN) {
        return MOVED_INVALID_DIRECTION;
    }

    switch (direction) {
        case LEFT:
            new_x--;
            break;
        case RIGHT:
            new_x++;
            break;
        case UP:
            new_y--;
            break;
        case DOWN:
            new_y++;
            break;
    }


    if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
        return MOVED_WALL;
    }
    if (map[new_y * width + new_x] == WALL) {
        return MOVED_WALL;
    }
    map[*player_y * width + *player_x] = EMPTY;
    if (dot_map[new_y * width + new_x] == DOT) {
        dot_map[new_y * width + new_x] = EMPTY;
    }
    map[new_y * width + new_x] = PLAYER;
    *player_y = new_y;
    *player_x = new_x;
    return MOVED_OKAY;
}

int move_ghost(int *ghost_y, int *ghost_x, char direction) {

    int newY = *ghost_y, newX = *ghost_x;
    if (direction!=LEFT&&direction!=RIGHT&&direction!=UP&&direction!=DOWN){
        return MOVED_INVALID_DIRECTION;
    }
    switch (direction) {

        case UP:

            newY--;

            break;

        case DOWN:

            newY++;

            break;

        case LEFT:

            newX--;

            break;

        case RIGHT:

            newX++;

            break;
    }


    // Check for wall or out of bounds
    if (newX < 0 || newX >= width || newY < 0 || newY >= height ) {
        return MOVED_WALL;
    }
    if(map[newY*width+newX]==WALL){
        return MOVED_WALL;
    }

    map[*ghost_y * width + *ghost_x] = dot_map[*ghost_y * width + *ghost_x];  // Clear the old position
    map[newY * width + newX] = GHOST;
    *ghost_x = newX;
    *ghost_y = newY;

    return MOVED_OKAY;

}

