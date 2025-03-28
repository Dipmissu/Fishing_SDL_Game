#pragma once

#include <SDL.h>
#include <string>
#include "texturemanager.h"
#include "textrenderer.h"

class Time{
private:
    int timeLeft;
    int lastTime;
    bool Running;

    TextureManager* g_textureManager;
    TextRenderer* g_textRenderer;

public:
    Time(TextureManager* textureManager, TextRenderer* textRenderer);

    void render(SDL_Renderer* renderer);
    void update();
    int getTime() const {return timeLeft;}
    bool isRunning() const {return Running;}

};
