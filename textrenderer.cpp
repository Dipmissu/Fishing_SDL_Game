#include "textrenderer.h"
#include <iostream>

using namespace std;

TextRenderer::TextRenderer(SDL_Renderer* renderer, const string& fontPath, int fontSize) {
    this->renderer = renderer;
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        cerr << "Fail to load font! " << TTF_GetError() << endl;
        exit(-1);
    }
}

TextRenderer::~TextRenderer() {
    if (font) {
        TTF_CloseFont(font);
    }
}

void TextRenderer::renderText(const string& text, SDL_Color color, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface) {
        cerr << "Lỗi tạo surface văn bản! " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        cerr << "Lỗi tạo texture văn bản! " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

