// textrenderer.h
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class TextRenderer {
private:
    TTF_Font* font;
    SDL_Renderer* renderer;

public:
    TextRenderer(SDL_Renderer* renderer, const string& fontPath, int fontSize);
    ~TextRenderer();

    void renderText(const string& text, SDL_Color color, int x, int y);
};

#endif

