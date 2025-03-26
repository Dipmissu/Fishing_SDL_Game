// Creature.h
#pragma once

#include <SDL.h>
#include <string>
#include "texturemanager.h"

using namespace std;

class Creature {
private:
    SDL_Rect g_rect;
    int g_speed;
    int g_value;
    bool g_collected;
    bool g_facingRight;
    string g_path;
    TextureManager* g_textureManager;

    // Animation
    int g_frameCount;
    int g_currentFrame;
    float g_frameTime;
    float g_frameDelay;

public:
    Creature(TextureManager* textureManager);
    ~Creature();

    void init(int x, int y, string path, int value);
    void update(float deltaTime, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
    void collect();
    void setPosition(int x, int y);
    const SDL_Rect& getRect() const { return g_rect; }
    int getValue() const { return g_value; }
    bool isCollected() const { return g_collected; }
};
