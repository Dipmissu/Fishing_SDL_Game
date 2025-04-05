// time.h
#ifndef TIME_H
#define TIME_H

#include <SDL.h>
#include <string>
#include "texturemanager.h"
#include "textrenderer.h"

class Time{
private:
    int g_timeLeft;
    int g_lastTime;

    TextureManager* g_textureManager;
    TextRenderer* g_textRenderer;

public:
    Time(TextureManager* textureManager, TextRenderer* textRenderer);

    void render(SDL_Renderer* renderer);
    void update();
    void reset();
    void addTime(int time);
    int getTime() const {return g_timeLeft;}

};

#endif // TIME_H

