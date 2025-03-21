// Hook.h
#pragma once

#include <SDL.h>

class Hook {
private:
    SDL_Rect g_base;
    SDL_Point g_tip;
    double g_angle;
    bool g_extending;
    double g_length;
    double g_speed;
    bool g_attached;
    bool g_movingLeft;
    int g_attachedGoldIndex;
    bool g_returned;

public:
    Hook(int x, int y);
    ~Hook();

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);

    void startExtend();
    void startRetract();
    void attachGold(int index, int goldSize);
    void detachGold();

    bool isExtending() const { return g_extending; }
    bool isAttached() const { return g_attached; }
    bool hasReturned() const { return g_returned; }
    int getAttachedGoldIndex() const { return g_attachedGoldIndex; }
    SDL_Point getTipPosition() const { return g_tip; }
};
