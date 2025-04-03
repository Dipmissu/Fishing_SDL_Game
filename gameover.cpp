// gameover.cpp
#include "gameover.h"
#include "constants.h"
#include <iostream>

GameOver::GameOver(const string& file, TextureManager* textureManager):
    fileName(file),
    highScore(0),
    g_textureManager(textureManager){
        loadHighScore();
    }

int GameOver::getHighScore() const{
    return highScore;
}

void GameOver::loadHighScore(){
    ifstream inFile(fileName);
    if(inFile.is_open()){
        inFile >> highScore;
        inFile.close();
    } else {
        highScore = 0;
        saveHighScore();
    }
}

void GameOver::updateHighScore(int newScore){
    if(newScore > highScore) highScore = newScore;
    saveHighScore();
}

void GameOver::saveHighScore() const{
    ofstream outFile(fileName);
    if(outFile.is_open()){
        outFile << highScore;
        outFile.close();
    }
}

void GameOver::render(SDL_Renderer* renderer){
    g_textureManager->draw("scoreboard",160,200,480,320,renderer);
}
