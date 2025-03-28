#include "score.h"
#include "constants.h"
#include <string>

using namespace std;

Score::Score(TextureManager* textureManager, TextRenderer* textRenderer) :
    score(0),
    g_textureManager(textureManager),
    g_textRenderer(textRenderer) {}

void Score::addPoints(int points) {
    score += points;
}

void Score::reset() {
    score = 0;
}

void Score::render(SDL_Renderer* renderer){
    string text = to_string(score);
    SDL_Color color = {75, 0, 130, 0};
    g_textureManager->draw("board", 20, 15, BOARD_WIDTH, BOARD_HEIGHT, renderer);
    g_textureManager->draw("coin", 73, 25, COIN_RADIUS, COIN_RADIUS, renderer);
    g_textRenderer->renderText(text, color, 26, 23);
}


