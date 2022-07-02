#include "ScoreBoard.h"

void ScoreBoard::addPlayerNameAndScore(string name, int score) {//saves plyer name and score to the scoreboard
    int overwrite;//variable storing user decision to everwrite players score i he already exists
    if (scoreboard.find(name) == scoreboard.end()) {//check if the player is already in the list, 
        scoreboard[name] = score;//if not saves player score immediately after his consent
    }
    else {
        cout << "Player: " << name << " already exists with the score: " << scoreboard[name] << "\n";;//program ask if you want to overwrite existing players score
        cout << "Do you wish to overwrite: \n";
        cout << "1: yes\n";
        cout << "2: no\n";
        cout << "Your choice: ";
        cin >> overwrite;//choosing whether to overwrite this player's previous score, player needs to type in 1 or 2.
        switch (overwrite) {
        case 1:
            scoreboard[name] = score;
            break;
        case 2:
            break;
        }
    }
}

void ScoreBoard::displayScoreboard() {//if user wants scoreboard is sorted, then displayed
    int position = 1;
    // Declare a multimap
    std::multimap<int, string> MM;

    // Insert every (key-value) pairs from
    // map M to multimap MM as (value-key)
    // pairs
    for (auto& it : scoreboard) {
        MM.insert({ it.second, it.first });
    }
    cout << "\n";
    //fallowing code displays 10 best players and their scores
    map<int, string>::reverse_iterator it;
    for (it = MM.rbegin(); it != MM.rend(); it++) {
        cout << position << ": " << it->second << ": " << it->first << "\n";
        position++;
        if (position == 11) {
            break;
        }
    }
}

//function saves scoreboard to the file//
void ScoreBoard::saveToFile() {
    std::fstream wyniki;
    wyniki.open("C:/Users/Damian Grzes³o/source/repos/Projects_JPO/Tetris/wyniki.txt", std::ios::out);

    for (map<string, int>::iterator letter = scoreboard.begin(); letter != scoreboard.end(); letter++) {
        wyniki << letter->first << "\n";
        wyniki << letter->second << "\n";
    }
    wyniki.close();
}

void ScoreBoard::clearScoreboard() {
    scoreboard.clear();//clears the whole map
}