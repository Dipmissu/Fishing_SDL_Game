#include "score.h"
#include "constants.h"
#include <string>
#include <iostream>

using namespace std;

Score::Score(TextureManager* textureManager, TextRenderer* textRenderer) :
    g_score(0),
    g_oldscore(0),
    g_flashTime(0),
    g_textureManager(textureManager),
    g_textRenderer(textRenderer) {}

void Score::addPoints(int points) {
    g_score += points;
    g_flashTime = SDL_GetTicks();
}

void Score::reset() {
    g_score = 0;
    g_oldscore = 0;
    g_flashTime = 0;
}

void Score::render(SDL_Renderer* renderer){
    int deltascore = g_score - g_oldscore;
    if(SDL_GetTicks() - g_flashTime > 1500)
    g_oldscore = g_score;
    string score_text = to_string(g_score);
    string deltascore_text = (deltascore < 0) ? to_string(deltascore) : "+" + to_string(deltascore);
    SDL_Color color = {0, 0, 0, 0};
    int posY = (deltascore != 0) ? 60 : - 20;
    g_textureManager->draw("board", 20, 15, BOARD_WIDTH, BOARD_HEIGHT, renderer);
    g_textureManager->draw("coin", 73, 25, COIN_RADIUS, COIN_RADIUS, renderer);
    if (deltascore != 0 && ((SDL_GetTicks() - g_flashTime) / 300) % 2 == 0) {
        g_textRenderer->renderText(deltascore_text, color, SCREEN_WIDTH / 2 - 72, posY);
        g_textureManager->draw("coin", SCREEN_WIDTH / 2 - 30, posY + 2, COIN_RADIUS, COIN_RADIUS, renderer);
    }
    g_textRenderer->renderText(score_text, color, 26, 23);
}


