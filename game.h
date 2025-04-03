// game.h
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <string>
#include <SDL_image.h>
#include "time.h"
#include "hook.h"
#include "box.h"
#include "score.h"
#include "sound.h"
#include "mussel.h"
#include "gameover.h"
#include "creature.h"
#include "explosion.h"
#include "texturemanager.h"
#include "textrenderer.h"

using namespace std;

enum GameState {MENU, PLAY, HELP, GAMEOVER, EXIT};

class Game {
private:
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    int g_timeLeft;
    int g_numberEntity;
    bool g_pause;
    bool g_ending;
    bool g_soundOn;
    bool g_musicOn;
    bool g_isRunning;
    bool g_touchPlay;
    bool g_touchHelp;
    bool g_touchExit;
    bool g_touchScreen;
    bool g_boxCollected;
    string g_buff;
    Uint32 g_lastTime;

    // Kích thước cửa sổ
    int g_screenWidth;
    int g_screenHeight;

    // Các đối tượng game
    Box* g_box;
    Hook* g_hook;
    Sound* g_sound;
    GameOver* g_gameover;
    Explosion* g_explosion;
    vector<Mussel*> g_mussel;
    vector<Creature*> g_creatures;

    Time* g_time;
    Score* g_score;
    TextRenderer* g_textRenderer;
    TextRenderer* g_textRendererTile;
    TextRenderer* g_textRendererScore;
    TextureManager* g_textureManager;

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
    GameState getGameState() const;
    void renderMenu();
    void handleMenuEvents();
    void handleHelpEvents();
    void handleGameOverEvents();

    SDL_Renderer* getRenderer() const { return g_renderer; }
    TextureManager* getTextureManager() const { return g_textureManager; }
    int getScreenWidth() const { return g_screenWidth; }
    int getScreenHeight() const { return g_screenHeight; }
};

#endif // GAME_H

