// game.h
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "hook.h"
#include "creature.h"
#include "mussel.h"
#include "score.h"
#include "time.h"
#include "explosion.h"
#include "texturemanager.h"
#include "textrenderer.h"

using namespace std;

enum GameState {MENU, PLAY, HELP, EXIT};

class Game {
private:
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    bool g_isRunning;
    int g_timeLeft;
    int g_gameIndex;
    bool g_touchPlay;
    bool g_touchHelp;
    bool g_touchExit;
    Uint32 g_lastTime;

    // Kích thước cửa sổ
    int g_screenWidth;
    int g_screenHeight;

    // Các đối tượng game
    Hook* g_hook;
    Explosion* g_explosion;
    vector<Mussel*> g_mussel;
    vector<Creature*> g_creatures;

    TextureManager* g_textureManager;
    TextRenderer* g_textRenderer;
    TextRenderer* g_textRendererTile;
    Score* g_score;
    Time* g_time;

    GameState g_gameState;

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
    int getgameIndex() const;
    void renderMenu();
    void handleMenuEvents();

    SDL_Renderer* getRenderer() const { return g_renderer; }
    TextureManager* getTextureManager() const { return g_textureManager; }
    int getScreenWidth() const { return g_screenWidth; }
    int getScreenHeight() const { return g_screenHeight; }
};
