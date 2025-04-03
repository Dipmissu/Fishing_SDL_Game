// box.h
#ifndef BOX_H
#define BOX_H

#include <SDL.h>
#include <string>
#include "textureManager.h"

using namespace std;

class Box {
private:
    SDL_Rect g_rect;
    int g_speed;
    int g_directionX;
    int g_directionY;
    bool g_collected;
    string g_state;

    TextureManager* g_textureManager;
public:
    Box(TextureManager* textureManager);
    ~Box();
    void init(int screenWidth, int screenHeight);
    void update(int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
    string state();
    void collect();
    void setPosition(int x, int y);
    bool isCollected() const { return g_collected; }
    const SDL_Rect& getRect() const { return g_rect; }

};

#endif // BOX_H
