// gameover.h
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include "texturemanager.h"

using namespace std;

class GameOver {
private:
    int highScore;
    string fileName;
    TextureManager* g_textureManager;
public:
    GameOver(const string &file, TextureManager* textureManager);
    ~GameOver();

    int getHighScore() const;
    void updateHighScore(int newScore);
    void saveHighScore() const;
    void loadHighScore();
    void render(SDL_Renderer* renderer);
};


#endif // GAMEOVER_H
