#pragma once
/*
* It'a a class for creating tetrominos of random shapes in grenn colour
*/

#include "Piece.h"
enum class Shape { L, T, Z, S, I, J, O };//Possible shapes for the piece

class PieceCreation
{
public:
	PieceCreation() {};//default constructor
	~PieceCreation() {};//default destructor
	Piece getPiece(const int x,const int y) const;//Creates a piece
};