// Creature.h
#pragma once

#include <SDL.h>
#include "texturemanager.h"

class Creature {
private:
    SDL_Rect g_rect;
    int g_speed;
    bool g_visible;
    TextureManager* g_textureManager;

    // Animation
    int g_frameCount;
    int g_currentFrame;
    float g_frameTime;
    float g_frameDelay;

public:
    Creature(TextureManager* textureManager);
    ~Creature();

    void init(int frameCount);
    void update(float deltaTime, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
};
