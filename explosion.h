// explosion.h
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL.h>
#include "constants.h"
#include "texturemanager.h"

class Explosion {
private:
    int xPos, yPos;
    int g_size;
    int g_frame;
    bool g_attached;
    float g_frameTime;
    float g_frameDelay;
    TextureManager* g_textureManager;

public:
    Explosion(TextureManager* textureManager);
    ~Explosion();
    void update();
    void render(SDL_Renderer* renderer);
    void init(int x, int y, int size);
    void isAttached();
};

#endif // EXPLOSION_H


