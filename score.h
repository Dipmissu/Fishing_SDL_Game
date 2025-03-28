#pragma once

#include <SDL.h>
#include <string>
#include "texturemanager.h"
#include "textrenderer.h"

using namespace std;

class Score {
private:
    int score;
    int oldscore;
    Uint32 flashTime;
    TextureManager* g_textureManager;
    TextRenderer* g_textRenderer;

public:
    Score(TextureManager* textureManager, TextRenderer* textRenderer);

    void addPoints(int points);
    void reset();
    int getScore() const {return score;}
    void render(SDL_Renderer* renderer);
};


