// mussel.h
#pragma once

#include <SDL.h>
#include <string>
#include "texturemanager.h"

using namespace std;

class Mussel {
private:
    SDL_Rect g_rect;
    int g_value;
    string g_path;
    bool g_collected;
    TextureManager* g_textureManager;

public:
    Mussel(TextureManager* textureManager);
    ~Mussel();

    void init(int x, int y, int w, int h, int val, string path);
    void render(SDL_Renderer* renderer);
    void collect();
    void setPosition(int x, int y);
    int getValue();

    const SDL_Rect& getRect() const { return g_rect; }
    bool isCollected() const { return g_collected; }
    string getPath() const {return g_path; }

};
