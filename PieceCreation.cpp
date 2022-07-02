#include "PieceCreation.h"
#include <random>


Piece PieceCreation::getPiece(const int x, const int y) const
{
	Piece l(x, y);//piece is initialized with certain coordinates

	//Randomiing shape selection
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 1000.0);

	Shape s = Shape((int)dist(mt) % 7);//randing shape

	if (s == Shape::L) {//depending on shape randed in randPiece function, ceartain shape is set
		l.setShape({
			{ 0,1,0 },
			{ 0,1,0 },
			{ 0,1,1 }
			});
	}
	else if (s == Shape::J) {
		l.setShape({
			{ 0,1,0 },
			{ 0,1,0 },
			{ 1,1,0 }
			});
	}
	else if (s == Shape::T) {
		l.setShape({
			{ 0,0,0 },
			{ 0,1,0 },
			{ 1,1,1 }
			});
	}
	else if (s == Shape::S) {
		l.setShape({
			{ 0,0,0 },
			{ 0,1,1 },
			{ 1,1,0 }
			});
	}
	else if (s == Shape::Z) {
		l.setShape({
			{ 0,0,0 },
			{ 1,1,0 },
			{ 0,1,1 }
			});
	}
	else if (s == Shape::O) {
		l.setShape({
			{ 0,0,0,0 },
			{ 0,1,1,0 },
			{ 0,1,1,0 },
			{ 0,0,0,0 }
			});
	}
	else if (s == Shape::I) {
		l.setShape({
			{ 0,1,0,0 },
			{ 0,1,0,0 },
			{ 0,1,0,0 },
			{ 0,1,0,0 }
			});
	}
	return l;

}


