/*
* It's a function that scores all players and their scores
* Can be used to display top10 player's, the ones with highest scores
*/

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>

using std::string, std::map, std::cout, std::cin;

class ScoreBoard {
private:
    map <string, int> scoreboard;//key is player name, int is for score
public:
    //constructor and destructor
    ScoreBoard() {};
    ~ScoreBoard() {};

    //methods
    void addPlayerNameAndScore(string name, int score);//saves player's name and score to her vector
    void displayScoreboard();//displays scoreboard sorted by scores
    void saveToFile();//saves scoreboard to text file
    void clearScoreboard();//method for clearing the whole scoreboard
};