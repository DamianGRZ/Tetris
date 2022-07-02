#include "Piece.h"

Piece::Piece(int x, int y) : px{ x }, py{ y }{};//construcor with x and y coordinates

Piece::Piece(const Piece& p2) {					//Copying constructor
	py = p2.py;
	px = p2.px;
	pshape = p2.pshape;
}

Piece::~Piece() {};

void Piece::moveRight() {//moveright method, changes pieces x coordinate
	px++;
}

void Piece::moveLeft() {//moveleft method, changes pieces x coordinate
	px--;
}

void Piece::moveDown() {//movedown method, changes pieces y coordinate
	py++;
}

void Piece::Rotate() {//Function to rotate the piece
	vector<vector<bool>> newShape{ pshape };

	for (unsigned int i = 0; i < pshape.size(); i++) {
		for (unsigned int j = 0; j < pshape[i].size();j++) {
			newShape[j][pshape.size() - i - 1] = pshape[i][j];
		}
	}
	setShape(newShape);//sets new shape as current shape
}