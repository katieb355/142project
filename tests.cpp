// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C" {
#include "defines.h"
#include "map.h"
#include "actor.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

TEST_CASE("test to check dots"){
    char dot_map_empty[]={
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
            EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
    };
    dot_map=dot_map_empty;
    width=9;
    height=9;

    CHECK(check_win()==YOU_WIN);
}

TEST_CASE("test dots left"){
    char dot_map_dots[]={
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
            DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,DOT,
    };
    dot_map=dot_map_dots;
    width=9;
    height=9;
    CHECK(check_win()==KEEP_GOING);

}

TEST_CASE("test no dots on tiny map"){
    char dot_map_tinyDots[]={
            EMPTY,EMPTY,
            EMPTY,EMPTY,
    };
    dot_map=dot_map_tinyDots;
    width=2;
    height=2;
    CHECK(check_win()==YOU_WIN);
}

// tests for is_wall

TEST_SUITE_END();

/* tests for actor.c */
TEST_SUITE_BEGIN("Actor tests");

// tests for sees_player
TEST_CASE("vert"){
    int player_y=2;
    int player_x=0;
    int ghost_y=0;
    int ghost_x=0;
    char map_test[]={
            EMPTY, EMPTY,PLAYER,
            EMPTY,WALL,WALL
    };
    map=map_test;
    width=3;
    height=2;
    CHECK(sees_player(player_y, player_x,ghost_y,ghost_x)==DOWN);
}
TEST_CASE("no vert"){
    int player_y=2;
    int player_x=2;
    int ghost_y=0;
    int ghost_x=0;
    char map_test[]={
            EMPTY, WALL,WALL,
            WALL,WALL,WALL
    };
    map=map_test;
    width=3;
    height=2;
    CHECK(sees_player(player_y, player_x,ghost_y,ghost_x)==SEES_NOTHING);
}
TEST_CASE("horz"){
    int player_y=1;
    int player_x=2;
    int ghost_y=1;
    int ghost_x=0;
    char test_map[]={
            EMPTY, WALL, WALL,
            PLAYER,EMPTY,EMPTY
    };
    map=test_map;
    height=2;
    width=3;
    CHECK(sees_player(player_y,player_x,ghost_y,ghost_x)==RIGHT);
}
TEST_CASE("no horz"){
    int player_y=1;
    int player_x=2;
    int ghost_y=1;
    int ghost_x=0;
    char test_map[]={
            EMPTY, WALL, WALL,
            WALL, WALL, PLAYER
    };
    map=test_map;
    height=2;
    width=3;
    CHECK(sees_player(player_y,player_x,ghost_y,ghost_x)==SEES_NOTHING);
}

// tests for move_player
TEST_CASE("test for move player") {

    int player_x = 1;
    int player_y = 1;

    char tiny_map[] = {WALL, WALL, WALL, WALL, PLAYER, DOT, WALL, DOT, WALL};
    map = tiny_map;
    height = 3;
    width = 3;
    char tiny_dot_map[] = {WALL, WALL, WALL, WALL, EMPTY, DOT, WALL, DOT, WALL};

    dot_map = tiny_dot_map;
    CHECK(move_player(&player_y, &player_x, RIGHT) == MOVED_OKAY);
    CHECK(move_player(&player_y, &player_x, LEFT) == MOVED_OKAY);
    CHECK(move_player(&player_y, &player_x, UP) == MOVED_WALL);
    CHECK(move_player(&player_y, &player_x, DOWN) == MOVED_OKAY);
    CHECK(move_player(&player_y, &player_x, RIGHT) == MOVED_WALL);
    CHECK(move_player(&player_y, &player_x, 'z') == MOVED_INVALID_DIRECTION);

}
// tests for move_ghost
TEST_CASE("ghost eat player") {
    int player_y = 0;
    int player_x = 0;
    int ghost_y = 0;
    int ghost_x = 0;
    char map_test[] = {
            PLAYER, EMPTY,
            EMPTY, WALL,
    };
    map = map_test;
    width = 2;
    height = 2;
    CHECK(sees_player(player_y, player_x, ghost_y, ghost_x) == EATING_PLAYER);
}

TEST_CASE("ghost move"){
    int ghost_y=1;
    int ghost_x=1;
    char dir=DOWN;
    char tiny_map[]={
            PLAYER, DOT,
            DOT,WALL
    };
    map=tiny_map;
    height=2;
    width=2;
    CHECK(move_ghost(&ghost_y,&ghost_x,dir)==MOVED_WALL);
}
TEST_CASE("ghost moved wrong"){
    int ghost_y=0;
    int ghost_x=0;
    char dir='z';
    char tiny_map[]={
            PLAYER, DOT,
            DOT,WALL
    };
    map=tiny_map;
    height=2;
    width=2;
    CHECK(move_ghost(&ghost_y,&ghost_x,dir)==MOVED_INVALID_DIRECTION);
}
TEST_CASE("ghost moved out"){
    int ghost_y=0;
    int ghost_x=0;
    char dir=UP;
    char tiny_map[]={
            PLAYER, DOT,
            DOT,WALL
    };
    map=tiny_map;
    height=2;
    width=2;
    CHECK(move_ghost(&ghost_y,&ghost_x,dir)==MOVED_WALL);
    CHECK(ghost_y==0);
    dir=LEFT;
    CHECK(move_ghost(&ghost_y,&ghost_x,dir)==MOVED_WALL);
    CHECK(ghost_x==0);
}
TEST_CASE("ghost moved on dot") {
    int ghost_y = 0;
    int ghost_x = 0;
    char dir = RIGHT;
    char tiny_map[] = {
            PLAYER, DOT,
            DOT, WALL
    };
    map = tiny_map;
    height = 2;
    width = 2;
    CHECK(move_ghost(&ghost_y, &ghost_x, dir) == MOVED_OKAY);
    CHECK(ghost_x==1);
}
TEST_CASE("ghost moved past player") {
    int ghost_y = 0;
    int ghost_x = 0;
    char dir = DOWN;
    char tiny_map[] = {
            PLAYER, DOT,
            DOT, WALL
    };
    map = tiny_map;
    height = 2;
    width = 2;
    CHECK(move_ghost(&ghost_y, &ghost_x, dir) == MOVED_OKAY);
    CHECK(ghost_y==1);
}
TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("Player does not hit ghost") {
    int player_x = 2, player_y = 2;
    int ghosts_x[NUM_GHOSTS] = {1, 4};
    int ghosts_y[NUM_GHOSTS] = {1, 4};
    CHECK(check_loss(player_x, player_y, ghosts_x, ghosts_y) == KEEP_GOING);
}

TEST_CASE("Player does not hit ghosts") {
    int player_x = 2, player_y = 2;
    int ghosts_x[NUM_GHOSTS] = {0, 4};
    int ghosts_y[NUM_GHOSTS] = {0, 4};
    CHECK(check_loss(player_x, player_y, ghosts_x, ghosts_y) == KEEP_GOING);
}
// test for check_loss
TEST_CASE("Player hits ghosts") {
    int ghost_y[2] = {0, 1};
    int ghost_x[2] = {0, 1};
    CHECK(check_loss(2, 2, ghost_y, ghost_x) == KEEP_GOING);
    CHECK(check_loss(2, 0, ghost_y, ghost_x) == KEEP_GOING);
    CHECK(check_loss(0, 2, ghost_y, ghost_x) == KEEP_GOING);
    CHECK(check_loss(0, 0, ghost_y, ghost_x) == YOU_LOSE);
    CHECK(check_loss(1, 1, ghost_y, ghost_x) == YOU_LOSE);
}

TEST_CASE("check_win test") {
    char tiny_map[] = {EMPTY, DOT, DOT, WALL};
    char tiny_dot_map[] = {EMPTY, DOT,DOT, EMPTY};
    map = tiny_map;
    dot_map = tiny_dot_map;
    width = 2;
    height = 2;
    CHECK(check_win() == KEEP_GOING);
}

TEST_CASE("check_win test no dots") {
    char tiny_map[] = {EMPTY, WALL, WALL, WALL};
    char tiny_dot_map[] = {EMPTY, EMPTY, EMPTY, EMPTY};
    map = tiny_map;
    dot_map = tiny_dot_map;
    width = 2;
    height = 2;
    CHECK(check_win() == YOU_WIN);
}

TEST_CASE("correct map test"){
    CHECK(load_map("notmap.txt",&height,&width)==NULL);
    CHECK(load_map("map.txt",&height,&width)!=NULL);
    CHECK(load_map("map2.txt",&height,&width)!=NULL);
}

TEST_CASE("test if wall"){
    CHECK(0==0);
}

TEST_SUITE_END();