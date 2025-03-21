// mussel.h
#pragma once

#include <SDL.h>
#include "texturemanager.h"

class Mussel {
private:
    SDL_Rect g_rect;
    int g_value;
    bool g_collected;
    TextureManager* g_textureManager;

public:
    Mussel(TextureManager* textureManager);
    ~Mussel();

    void init(int x, int y, int w, int h, int val);
    void render(SDL_Renderer* renderer);
    void collect();
    void setPosition(int x, int y);

    const SDL_Rect& getRect() const { return g_rect; }
    int getValue() const { return g_value; }
    bool isCollected() const { return g_collected; }
};
