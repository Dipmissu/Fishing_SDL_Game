// gameover.h
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class GameOver {
private:
    int highScore;
    string fileName;
public:
    GameOver(const string &file);
    ~GameOver();

    int getHighScore() const;
    void updateHighScore(int newScore);
    void saveHighScore() const;
    void loadHighScore();
};


#endif // GAMEOVER_H
