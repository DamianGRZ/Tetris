#pragma once
#include <iostream>
#include <SDL.h>//library for images redenreing
#include <vector>
#include <map>
#include <string>
#include <fstream>//saving to file, and reading from file
#include <windows.h>
#include <stdlib.h>//system("CLS")

#include "Constants.h"
#include "Piece.h"//includes piece class
#include "PieceCreation.h"
#include "pile.h"
#include "ScoreBoard.h"

//using std, so we don't have to write std before every call
using std::cout, std::cin, std::endl;
using std::vector, std::map, std::string;


extern SDL_Renderer* renderer;//from SDL, renderer initialization
extern SDL_Window* window;//from SDL, window initialization

extern gameState state;//game state initialization to it;s first state

extern int frameCount, timeFPS, lastFrame;//variables to measure game time
extern bool left, right, down, up;///variables checking which key was pressed

//windows height and width (in number of tiles)
extern unsigned int windowheight;//screen width in number of tiles, the same as the pile size
extern unsigned int windowwidth;//screen width in number of tiles, the same as the pile size

extern int lines;//saves number of lines the player completed
extern int score;//saves number of points player collected 

extern PieceCreation piececreation;//creates class which creates pieces
extern Piece piece; //creation of the first piece
extern Pile pile;//pile initialization

class Globals {
public:
    Globals() {};
    void nextPiece();
    bool outofbounds(const Piece& piece2);
    bool checklanded();
    bool checkpilecollision(const Piece& piece2);
    bool checkanycollision(const Piece& piece2);
    void moveleft();
    void moveright();
    void movedown();
    void rotate();
    void update();
    void input();
    void drawpiece(Piece piece);
    void drawPile(Pile pile);
    void render();
    void tick();
};