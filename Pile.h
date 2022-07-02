/*
* Class pile
* Responsible for holding all pieces that landed, adding new ones, ckecking rows and removing full ones
*/
#pragma once
#include <iostream>
#include <SDL.h>//library for images redenreing
#include <vector>
#include "Piece.h"

using std::cout, std::cin, std::endl;
using std::vector;

class Pile {
private:
    int pile_width;
    int pile_height;
    vector <vector<bool>> pile;
public:
    Pile(int width = 10, int height = 20) : pile_width{ width }, pile_height{ height } {
        //initializes the pile dimensions/ makes correct sizes
        pile.resize(pile_width);
        for (int i = 0; i < pile_width; i++)
            pile[i].resize(pile_height, false);
    }

    //getters
    int getPileWidth() const { return pile_width; }

    int getPileHeight() const { return pile_height; }

    vector <vector<bool>> getPile() const { return pile; }

    

    //methods
    void addPiece(const Piece& p);//adds piece to the pile
    void removeRow(int row);//removes a full row
    int checkRows();//zmieniæ typ funkcji na int przy robieniu puntkacji
    void pileClear();//clears pile after the game
};
