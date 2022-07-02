#include "Globals.h"
//Function orginizing next pieces
void Globals::nextPiece() {
    Piece followingpiece = piececreation.getPiece(3, 0);//creating new piece in point (3,1)
    piece = followingpiece;

    state = gameState::fallingpiece_state;//changening game state from getrandompiece_state to fallingpiece_state
}


bool Globals::outofbounds(const Piece& piece2) {//check if piece is out of bounds (to the left, right and down
    //Getting piece coordiates
    int x = piece2.getX();
    int y = piece2.getY();

    //getting piece's shape
    auto s = piece2.getShape();

    for (unsigned int i = 0; i < s.size(); i++)
        for (unsigned int j = 0; j < s[0].size(); j++)
            if (s[i][j] && (i + x >= windowwidth || j + y >= windowheight || i + x < 0))//conditions for stating piece is outside the board
                return true;

    return false;
}

//check if the piece landed on the end of the board or the pile//
bool Globals::checklanded() {
    int x = piece.getX();
    int y = piece.getY();

    auto shape = piece.getShape();//get piece shape

    for (unsigned int i = 0; i < shape.size(); i++)
        for (unsigned int j = 0; j < shape[0].size(); j++)
            if (((y + j + 1) >= windowheight && shape[i][j]) ||//checking if the piece landed on the end of the board
                (y + j + 1 >= 0 && x + i >= 0 && shape[i][j] && pile.getPile()[x + i][y + j + 1])) {//checking if the piece landed on the pile
                state = gameState::fallenpiece_state;
                return true;
            }
    return false;

}

//check if the piece landed on the end of the board or the pile 
bool Globals::checkpilecollision(const Piece& piece2) {
    int x = piece2.getX();
    int y = piece2.getY();

    auto s = piece2.getShape();

    for (unsigned int i = 0; i < s.size(); i++)
        for (unsigned int j = 0; j < s[0].size(); j++)
            if ((x + i >= 0 && x + i < windowwidth && y + j >= 0 && y + j < windowheight) && (pile.getPile()[x + i][y + j] && s[i][j]))
            {
                return true;//There was a collision
            }
    return false;//There was no collision
}

bool Globals::checkanycollision(const Piece& piece2) {//uses checkpilecollision and outofbounds functions
    return checkpilecollision(piece2) || outofbounds(piece2);
}


//functiosn for piece movement
//First they check if the move is possible on pieces copy by calling other functions
//if move is possible it's executed on original piece using it's methods
void Globals::moveleft() {
    Piece p2 = Piece{ piece };//Piece copying
    p2.moveLeft();//moving pieces copy

    if (!checkanycollision(p2)) {//checking if action is possible without collision
        piece.moveLeft();//movement of otiginal piece
    }
}

void Globals::moveright() {
    Piece p2 = Piece{ piece };
    p2.moveRight();

    if (!checkanycollision(p2)) {
        piece.moveRight();
    }
}

void Globals::movedown() {
    Piece p2 = Piece{ piece };
    p2.moveDown();

    if (!checkanycollision(p2)) {
        piece.moveDown();
        checklanded();
    }
}

void Globals::rotate() {
    Piece p2 = Piece{ piece };
    p2.Rotate();//calling rotate method

    if (!checkanycollision(p2)) {
        piece.Rotate();
    }
}

//This function updates game with the actions taken by the user, and changes brought by,changes in game states
void Globals::update() {
    if (left) moveleft();//call moveleft() function if left event is true
    if (right) moveright();
    if (up) rotate();
    if (down) movedown();
    if (state == gameState::getrandompiece_state) nextPiece();//if gamestate is in getrandompiece_stat, update funtion calls nextpiece() function, to get next piece
    if (state == gameState::fallenpiece_state) {
        pile.addPiece(piece);//if there was no collision with the pile add piece  to the pile
        state = gameState::getrandompiece_state;//change game state
    }
    if (state == gameState::fallingpiece_state) {
        checkpilecollision(piece);
        int lines_moved_in_one_check = pile.checkRows();
        if (lines_moved_in_one_check > 0) {
            lines += lines_moved_in_one_check;//adding to the total number of removed lines, lines removed during one checks
            switch (lines_moved_in_one_check) {//adding to player's score according to the number of lines, more lines = even more point's
            case 0: break;
            case 1: score += 40 * (lines / 10 + 1);
                break;
            case 2: score += 100 * (lines / 10 + 1);
                break;
            case 3: score += 300 * (lines / 10 + 1);
                break;
            case 4: score += 1200 * (lines / 10 + 1);
                break;
            }
            system("CLS");//Clears command window
            cout << "lines:" << lines << " \tlevel:" << lines / 10 << "      score: " << score << "\n";//Display current player score
        }

    }
}

//takes input from the keyboard and mouse
void Globals::input() {
    SDL_Event event;//initializes SDL library event variable
    left = right = down = up = 0;//zeroes all event variables to pass to update function, nothing is left from previous call
    while (SDL_PollEvent(&event)) {// in a loop we check events
        if (event.type == SDL_QUIT)  state = gameState::gameover_state;//if event type was to quit, change game state to "gameover_state"
        switch (event.type) {
        case SDL_KEYDOWN://if key is pressed down, change correct event variable
            switch (event.key.keysym.sym) {// keysym reports keys presses and releases
            case SDLK_LEFT:
                left = 1;
                break;
            case SDLK_UP:
                up = 1;
                break;
            case SDLK_DOWN:
                down = 1;
                break;
            case SDLK_RIGHT:
                right = 1;
                break;
            }
        }
    }
};

//Drawing functions
extern SDL_Rect rect;//template for rectangles

void Globals::drawpiece(Piece piece) {//functions which drawns bock with their shapes and colour
    auto shape = piece.getShape();
    SDL_Color color = piece.getColor();
    for (unsigned int i = 0; i < shape.size(); i++) {
        for (unsigned int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) { // pieces shapes are contained in rectangular blocks, but we only draw their shapes
                rect.x = (piece.getX() + i) * TILE_SIZE;//position of tile is where we are in the piece and piece coordinate on x axis.
                rect.y = (piece.getY() + j) * TILE_SIZE;//position of tile is where we are in the piece and piece coordinate on y axis.
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);//setting color for interior
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//setting color for outline
                SDL_RenderDrawRect(renderer, &rect);

            }
        }
    }
}

// pile plays the role of the pile as well as the board with a grid//
// depending on piles bollean value tiles collor is different

void Globals::drawPile(Pile pile) {//functions for drawing pile
    auto shape = pile.getPile();
    for (unsigned int i = 0; i < shape.size(); i++) {//10 is number of tiles horizontally
        for (unsigned int j = 0; j < shape[i].size(); j++) { //20 is number of tiles diagonally
            if (shape[i][j]) {          //if pile part is true, it means a block fallend there, it's drawn purple
                rect.x = i * TILE_SIZE;
                rect.y = j * TILE_SIZE;
                SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);//setting color for interior
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 219, 219, 219, 255);//setting color for outline
                SDL_RenderDrawRect(renderer, &rect);
            }
            else {                      //if pile part is false, it means a block wasn't there, it's drawn black
                rect.x = i * TILE_SIZE;
                rect.y = j * TILE_SIZE;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//setting color for interior
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 219, 219, 219, 255);//setting color for outline
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

//Function for rendering graphics
void Globals::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);//clearing renderer 
    //fallowing dealys so that change does not happen to quickly
    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / 60)) {
        SDL_Delay((1000 / 60) - timerFPS);
    }
    drawPile(pile);//drawning existing pile using function
    drawpiece(piece);//drawning existing piece using function
    SDL_RenderPresent(renderer);//rendering surrenct game image
}

//performs a move down every set time depending on player's level in game(higher level, shorter time)
void Globals::tick() {
    Piece p2 = Piece{ piece };
    movedown();
    if (p2.getY() == piece.getY()) {//je¿eli po wykonaniu ruchu w dó³ na kopi klocek  siê nie ruszy³ , to znaczy ¿e z czymœ koliduje i nie jest mo¿liwe wykonanie ruchu, gra siê koñczy 
        state = gameState::gameover_state;
    }
}