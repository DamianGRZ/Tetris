#include "Pile.h"
#include "Constants.h"

//This method adds piece to the pile after it fell down//
void Pile::addPiece(const Piece & p) {
    int x = p.getX();
    int y = p.getY();

    vector <vector<bool>> shape = p.getShape();

    for (int i = shape.size() - 1; i >= 0; i--) {//rows means y's ---

        for (int j = shape[i].size() - 1; j >= 0; j--) {//columns means x's |||
            if (shape[i][j] == 1) {
                pile[i + x][y + j] = true;
            }

        }

    }

}
 
//This method checks if rows are full//
int Pile::checkRows() {

    int removed = 0; //clearing removed lines counter during one check
    for (unsigned int j = 0; j < pile[0].size(); j++) {
        bool full = true;// full line indicator
        for (unsigned int i = 0; i < pile.size(); i++) {//horizontal check
            if (!pile[i][j]) {//if at least one element of the line = 0:
                full = false;//full line indicator is turned false
            }

        }
        if (full == true) {//if full line indicator == true, then removeRow function is called, removed lines counter is incremented
            removeRow(j);
            removed++;//incrementing number of lines removed during one chceck
        }
    }
    return removed;//removed lines counter is returned to count the player score.
}

//This function removes full rows, and copies elements above them to their position so it looks like pile is falling down
void Pile::removeRow(int row) {//removes certain full row in the pile
    for (unsigned int i = 0; i < pile.size(); i++) {//horizontally
        pile[i][row] = false;
    }

    for (int j = row; j >= 1; j--) {//this loop goes row after row
        for (unsigned int i = 0; i < pile.size(); i++) {//this goes horizaontally, column after column -> lub <-
            pile[i][j] = pile[i][j - 1];
        }
    }
}

//This method clears the whole pile after game is over so it's ready for the next game//
void Pile::pileClear() {
    for (unsigned int j = 0; j < pile[0].size(); j++) {//diagonally row after row
        for (unsigned int i = 0; i < pile.size(); i++) {//horizontally
            pile[i][j] = false;
        }
    }

}
