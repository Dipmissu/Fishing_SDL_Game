// game.h
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "hook.h"
#include "creature.h"
#include "mussel.h"
#include "texturemanager.h"

using namespace std;

class Game {
private:
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    bool g_isRunning;
    int g_score;
    int g_timeLeft;
    Uint32 g_lastTime;

    // Kích thước cửa sổ
    int g_screenWidth;
    int g_screenHeight;

    // Các đối tượng game
    Hook* g_hook;
    vector<Creature*> g_creatures;
    vector<Mussel*> g_mussel;

    // Texture manager
    TextureManager* g_textureManager;

public:
    Game();
    ~Game();

    bool init(const string& title, int width, int height);
    void createMussel();
    void createCreatures();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() const;

    SDL_Renderer* getRenderer() const { return g_renderer; }
    TextureManager* getTextureManager() const { return g_textureManager; }
    int getScreenWidth() const { return g_screenWidth; }
    int getScreenHeight() const { return g_screenHeight; }
};
