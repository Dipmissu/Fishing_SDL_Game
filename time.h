// time.h
#pragma once

#include <SDL.h>
#include <string>
#include "texturemanager.h"
#include "textrenderer.h"

class Time{
private:
    int g_timeLeft;
    int g_lastTime;
    bool g_running;

    TextureManager* g_textureManager;
    TextRenderer* g_textRenderer;

public:
    Time(TextureManager* textureManager, TextRenderer* textRenderer);

    void render(SDL_Renderer* renderer);
    void update();
    void addTime(int time);
    int getTime() const {return g_timeLeft;}
    bool isRunning() const {return g_running;}

};
