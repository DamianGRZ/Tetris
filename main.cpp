#include "Globals.h"

//using std, so we don't have to write std before every call
using std::cout, std::cin, std::endl;
using std::vector, std::map, std::string;

SDL_Renderer* renderer;//from SDL, renderer initialization
SDL_Window* window;//from SDL, window initialization


gameState state = gameState::getrandompiece_state;//game state initialization to it;s first state

int frameCount, timeFPS, lastFrame;//variables to measure game time
bool left, right, down, up;///variables checking which key was pressed

//windows height and width (in number of tiles)
unsigned int windowheight = 20;//screen width in number of tiles, the same as the pile size
unsigned int windowwidth = 10;//screen width in number of tiles, the same as the pile size

int lines = 0;//saves number of lines the player completed
int score = 0;//saves number of points player collected 

PieceCreation piececreation;//creates class which creates pieces
Piece piece = piececreation.getPiece(1, 0);//creation of the first piece
Pile pile(windowwidth, windowheight);//pile initialization
Globals globals;


//Drawing functions
SDL_Rect rect;//template for rectangles


int main(int argc, char* argv[]) {
   //local variables//
   string action = "1";//player choose variable
   string playerName = "oo";//player name variable
   string halloffameaction = "1";//player choose variable in the hall of fame submenu
   string scorestring;//player score in string format
   ScoreBoard hallOfFame;//variable of class ScoreBoard type, for operating scoreboard
   std::fstream wyniki;//file for scores, variable
   string savescore = "1";//flag conataining players will to save his nickname and score
   vector<int> level_speed{ 60, 48, 37, 28, 21, 16, 11, 8, 6, 4, 3, 2 };//pieces falling intervals
   int falldown = 0;//helping variable for block falling speed, count's up to level_speed
   int screenWidth = WIDTH;//initialization of screen width with constant
   int screenHight = HEIGHT;//initialization of screen height with constant
   rect.w = rect.h = TILE_SIZE;//initialization of tile sizes
   ///////////////////

   //This function passes scores from wyniki.txt to scoreboard class
   cout << "*************************************\n";
   cout << "*         Welcome to Tetris         *\n";

   cout << "*       Author: Damian Grzeslo      *\n";
   cout << "\n*************************************\n";
   wyniki.open("C:/Users/Damian Grzes³o/source/repos/Projects_JPO/Tetris/wyniki.txt",std::ios::in);
   if (wyniki.is_open()) {//chceck if file is open
       while (wyniki.eof() == 0){//chceck if we are not at the end of the file
           std::getline(wyniki, playerName);//saves player name into a variable
           if (wyniki.eof() == 0)
               std::getline(wyniki, scorestring);//saves player score into a variable
           else
               break;
           hallOfFame.addPlayerNameAndScore(playerName, std::stoi(scorestring));//passes variables into the class with the use of function
       }
   }
   wyniki.close();//file is closed
   do {
       falldown = 0;//clearing it
       lines = 0; //clearing lines count
       state = gameState::getrandompiece_state;//switching game state to rand new piece
       if (SDL_Init(SDL_INIT_EVERYTHING)) {   //inittialization of SDL library, checking if it was correctly initialized
           cout << "Cannot initialize SDL ... exiting";
           break;//leaves the loop, ends program
       }
       static int lastTime = 0;

       cout << "\nMain menu:\n";
       cout << "1: Play\n" << "2: Display hall of fame\n" << "3: Controls\n" << "4: Exit\n";
       cout << "Your choice: ";
       cin >> action;//choosing action in main menu
       while (action != "1" && action != "2" && action != "3" && action != "4") {//checking if action was one of proposed, if not player is asked to type in again
           cout << "There is no such action, choose again:\n";
           cout << "1: Play\n" << "2: Enter hall of fame\n" <<"3: Controls\n" << "4: Exit\n";
           cout << "Your choice: ";
           cin >> action;
       } 
       switch (std::stoi(action)) {//Playing different action according to layers choice
       case 1:
           //system("CLS");
           cout << "lines:" << lines << " \tlevel:" << lines / 10 << "      score: " << score << "\n";//display of lines, level and score.
           if (SDL_CreateWindowAndRenderer(screenWidth, screenHight, 0, &window, &renderer) < 0) {//creates window adn renderer
               cout << "Couldn't create window or/and renderer ... exiting \n";//dispalys message that creation was unsuccessful 
               break;//exits 
           }
           else {
               SDL_SetWindowTitle(window, "Tetris Game - Damian Grzeslo");//Sets window title
           }

           while (state != gameState::gameover_state) {//games loop, as long as games state is not gameover_state, the game lasts
               lastFrame = SDL_GetTicks();//Get the number of milliseconds since SDL library initialization.
               if (lastFrame >= (lastFrame + 1000)) {
                   lastTime = lastFrame;
                   frameCount = 0;

               }
               globals.input();//checks if there was any input, like key pressing or exiting window
               globals.update();//updates game situation according to the input or game states
               globals.render();//actualizes updated game situation, draws it again
               if (down == 0) {//checks if key for down movement is pressed down, if yes then movement every set time is switched off
                   falldown++;
               }
               if (falldown >= level_speed[lines / 10]) {//constrols down movements of the block every set time
                   globals.tick();//block falls down
                   falldown = 0;
               }
           }
           Sleep(3000);//waiting, so that player sees how he lost
           pile.pileClear();//clears pile after loss
           SDL_DestroyRenderer(renderer);//destruction of SDL library renderer
           SDL_DestroyWindow(window);//destruction of SDL library window
           SDL_Quit();              //exiting SDL Library
           cout << "GAME OVER\n";//in command window printing game over
           cout << "Do you wish to save your nickname and score: \n";
           cout << "1: yes\n";
           cout << "2: no\n";
           cout << "Your choice: ";
           cin >> savescore;//choosing, player needs to type in 1 or 2.
           while (savescore != "1" && savescore != "2") {//checking if action was one of proposed, if not player is asked to type in again
               cout << "There is no such action, choose again:\n";
               cout << "1: yes\n";
               cout << "2: no\n";
               cout << "Your choice: ";
               cin >> savescore;//choosing, player needs to type in 1 or 2.
           }
           switch (stoi(savescore)) {
           case 1:
               cout << "\nThen type in your nickname: ";
               cin >> playerName;
               hallOfFame.addPlayerNameAndScore(playerName, score);//saving players score
               break;
           case 2:
               break;
           }
           score = 0;//clearing score
           break;
       case 2:
           cout << "\nHall of fame menu: ";
           cout << "\n1: Display hall of fame";
           cout << "\n2: Delete hall of fame";
           cout << "\nYour action: ";
           cin >> halloffameaction;
           while (halloffameaction != "1" && halloffameaction != "2") {//checking if action was one of proposed, if not player is asked to type in again
               cout << "There is no such action, choose again:\n";
               cout << "\n1: Display hall of fame" << "\n2: Delete hall of fame";
               cout << "Your choice: ";
               cin >> halloffameaction;
           }
           switch (std::stoi(halloffameaction)) {
           case 1:
               hallOfFame.displayScoreboard();//Displaying scoreboard to the user
               break;
           case 2:
               cout << "\nAre you sure this action will result in scoreboard irrevrsible clearing: ";
               cout << "\n1: I am sure";
               cout << "\n2: Stop";
               cout << "\nYour choice: ";
               cin >> halloffameaction;
               if (halloffameaction == "1") {
                   hallOfFame.clearScoreboard();//clearing hall of fame by the user
                   cout << "\nScoreboard was cleared: \n";
               }
               else
                   cout << "\nScoreboard was not cleared: \n";
               break;
           }
           break;
       case 3:
           //Displaying key control
           cout << "\nControls: \n";
           cout << "Move down: \x18 key\n";
           cout << "Move up: \x19 key\n";
           cout << "Move right: -> key\n";
           cout << "Move left: <- key\n";
       }//switch end
    } while (std::stoi(action) != 4);
    hallOfFame.saveToFile();//savng scoreboard to the file
 
    return 0;
}