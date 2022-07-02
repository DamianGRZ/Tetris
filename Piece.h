/*
* It'a a class for storing tetrominos of random shape and green colour.
* It has four basic methods, three for evement and one for tetromino rotation
*/

#pragma once
#include <iostream>
#include <SDL.h>//library for images redenreing
#include <vector>


using std::cout, std::cin, std::endl;
using std::vector;

class Piece
{
private:
	SDL_Color pcolor = { .r = 0, .g = 255, .b = 0 };//color of the tetromino
	vector<vector<bool>> pshape = { { 0,1,0 },
	{ 0,1,0 },
	{ 0,1,1 } };//shape of the tetromino
	int px, py;//location of the tetromino on the grid
public:
	Piece(int x, int y);
	Piece(const Piece& p2);
	~Piece(); //desctructor

	//getters
	int getX() const { return px; }
	int getY() const { return py; }
	vector<vector<bool>> getShape() const { return pshape; }
	SDL_Color getColor() const { return pcolor; }

	//setters
	void setX(const int x) { this->px = x; }
	void setY(const int  y) { this->py = y; }
	void setShape(const vector<vector<bool>>& newShape) { pshape = newShape; }

	//Methods declarations
	void Rotate();
	void moveRight();
	void moveLeft();
	void moveDown();
};
