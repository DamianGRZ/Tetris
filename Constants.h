#pragma once
//Contains some constants
#define TILE_SIZE 30;//Tiles in the program are 30x30 pixels
#define WIDTH 300;
#define HEIGHT 600;


enum class gameState {//game states in which game can be
    getrandompiece_state, fallingpiece_state, fallenpiece_state, gameover_state
};