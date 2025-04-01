// game.cpp
#include "game.h"
#include "sound.h"
#include "score.h"
#include "constants.h"
#include "textrenderer.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game() :
    g_window(nullptr),
    g_renderer(nullptr),
    g_lastTime(0),
    g_isRunning(false),
    g_pause(false),
    g_touchPlay(false),
    g_touchHelp(false),
    g_touchExit(false),
    g_touchScreen(false),
    g_timeLeft(TIME),
    g_screenWidth(SCREEN_WIDTH),
    g_screenHeight(SCREEN_HEIGHT),
    g_box(nullptr),
    g_hook(nullptr),
    g_score(nullptr),
    g_time(nullptr),
    g_soundOn(true),
    g_musicOn(true),
    g_boxCollected(true),
    g_explosion(nullptr),
    g_textureManager(nullptr),
    g_textRendererTile(nullptr),
    g_textRenderer(nullptr) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game() {
    clean();
}

bool Game::init(const string& title, int width, int height) {
    g_screenWidth = width;
    g_screenHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_screenWidth, g_screenHeight, SDL_WINDOW_SHOWN);

    if (!g_window) {
        cerr << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (!g_renderer) {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        cerr << "SDL_mixer could not initialize! Mixer Error: " << Mix_GetError() << endl;
    }

    if (TTF_Init() == -1) {
        cerr << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }

    g_textureManager = new TextureManager();
    g_textRenderer = new TextRenderer(g_renderer,"font/PatuaOne-Regular.ttf",FONT_SIZE);
    g_textRendererTile = new TextRenderer(g_renderer,"font/Daydream.ttf",FONT_SIZE_TILE);

    createMussel();
    createCreatures();

    g_sound = new Sound();
    g_explosion = new Explosion(g_textureManager);
    g_time = new Time(g_textureManager,g_textRenderer);
    g_score = new Score(g_textureManager,g_textRenderer);
    g_hook = new Hook(g_screenWidth / 2 - FISHER_WIDTH / 2,FISHER_DISTANT);

    struct TextureData {
        string id;
        string path;
    };

    vector<TextureData> textures = {
        {"creature_1", "image/creature_1.png"},
        {"creature_2", "image/creature_2.png"},
        {"creature_3", "image/creature_3.png"},
        {"creature_4", "image/creature_4.png"},
        {"background", "image/background.png"},
        {"mussel", "image/mussel.png"},
        {"fisher", "image/fisher.png"},
        {"button","image/button.png"},
        {"board", "image/board.png"},
        {"bomb", "image/bomb.png"},
        {"hook", "image/hook.png"},
        {"coin", "image/coin.png"},
        {"time", "image/time.png"},
        {"menu","image/menu.png"},
        {"box","image/box.png"},

        // Tải texture explosion
        {"1","image/explosion/Explosion_1.png"},
        {"2","image/explosion/Explosion_2.png"},
        {"3","image/explosion/Explosion_3.png"},
        {"4","image/explosion/Explosion_4.png"},
        {"5","image/explosion/Explosion_5.png"},
        {"6","image/explosion/Explosion_6.png"},
        {"7","image/explosion/Explosion_7.png"},
        {"8","image/explosion/Explosion_8.png"},
        {"9","image/explosion/Explosion_9.png"},
        {"10","image/explosion/Explosion_10.png"},

        // Tải texture box
        {"x2","image/x2.png"},
        {"minus","image/minus.png"},
        {"extratime","image/extratime.png"}
    };

    for (const auto& texture : textures) {
        if (!g_textureManager->loadTexture(texture.id, texture.path, g_renderer)) {
            cerr << "Failed to load " << texture.id << " texture!" << endl;
        }
    }

    g_soundOn = true;
    g_musicOn = true;
    g_isRunning = true;
    g_gameState = MENU;
    g_touchPlay = false;

    g_sound->playBackgroundMusic(g_musicOn);

    return true;
}

void Game::renderMenu() {
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer);

    g_textureManager->draw("menu",0,0,g_screenWidth,g_screenHeight,g_renderer);

    SDL_Color textColor = {0, 0, 0, 0};
    SDL_Color touchColor = {255,255,255,255};
    g_textRendererTile->renderText("Fishing Game!", textColor, g_screenWidth / 2 - 180, 20);

    // Vẽ nút Play
    g_textureManager->draw("button",g_screenWidth / 2 - 90, 240, 180, 80, g_renderer);
    if(g_touchPlay == true) g_textRendererTile->renderText("Play", touchColor, g_screenWidth / 2 - 60, 257);
    else g_textRendererTile->renderText("Play", textColor, g_screenWidth / 2 - 60, 257);

    // Vẽ nút Help
    g_textureManager->draw("button",g_screenWidth / 2 - 90, 310, 180, 80, g_renderer);
    if(g_touchHelp == true) g_textRendererTile->renderText("Help", touchColor, g_screenWidth / 2 - 60, 328);
    else g_textRendererTile->renderText("Help", textColor, g_screenWidth / 2 - 60, 328);

    // Vẽ nút Exit
    g_textureManager->draw("button",g_screenWidth / 2 - 90, 380, 180, 80, g_renderer);
    if(g_touchExit == true) g_textRendererTile->renderText("Exit", touchColor, g_screenWidth / 2 - 60, 398);
    else g_textRendererTile->renderText("Exit", textColor, g_screenWidth / 2 - 60, 398);

    SDL_RenderPresent(g_renderer);
}

void Game::handleMenuEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            g_gameState = EXIT;
            g_isRunning = false;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        g_touchPlay = (x >= g_screenWidth / 2 - 90 && x <= g_screenWidth / 2 + 90 && y >= 250 && y <= 310);
        g_touchHelp = (x >= g_screenWidth / 2 - 90 && x <= g_screenWidth / 2 + 90 && y >= 320 && y <= 380);
        g_touchExit = (x >= g_screenWidth / 2 - 90 && x <= g_screenWidth / 2 + 90 && y >= 380 && y <= 450);

        if (event.type == SDL_MOUSEBUTTONDOWN) {

            // Kiểm tra click vào nút Play
            if (x >= g_screenWidth / 2 - 90 && x <= g_screenWidth / 2 + 90 && y >= 250 && y <= 310) {
                g_gameState = PLAY;
            }

            // Kiểm tra click vào nút Help
            if (x >= g_screenWidth / 2 - 90 && x <= g_screenWidth / 2 + 90 && y >= 320 && y <= 380) {
                g_gameState = HELP;
            }

            // Kiểm tra click vào nút Exit
            if (x >= g_screenWidth / 2 - 90 && x <= g_screenWidth / 2 + 90 && y >= 380 && y <= 450) {
                g_gameState = EXIT;
                g_isRunning = false;
            }
        }
    }
}

void Game::createCreatures(){
    for(auto& creature : g_creatures){
        delete creature;
    }
    g_creatures.clear();

    vector<string> path{"creature_4", "creature_3", "creature_2", "creature_1"};

    for (int i = 0; i < CREATURE_NUMBER; i++) {
        bool overlap;
        int x, y;
        do {
            x = rand() % (g_screenWidth - 150) + 20;
            y = rand() % (g_screenHeight - 300) + 250;
            overlap = false;
            for (const auto& creature : g_creatures) {
                if (abs(x - creature->getRect().x) < CREATURE_RADIUS * 2 &&
                    abs(y - creature->getRect().y) < CREATURE_RADIUS * 2) {
                    overlap = true;
                    break;
                }
            }
        } while (overlap);
        int pos = rand() % 4;
        Creature* creature = new Creature(g_textureManager);
        creature->init(x, y, path[pos], (pos + 1) * 100);
        g_creatures.push_back(creature);
    }
}

void Game::createMussel() {
    for (auto& mussel : g_mussel) {
        delete mussel;
    }
    g_mussel.clear();

    vector<string> path{"bomb", "mussel"};

    for (int i = 0; i < MUSSEL_NUMBER; i++) {
        int size = rand() % 20 + 35;
        bool overlap;
        int x, y;
        do {
            x = rand() % (g_screenWidth - size);
            y = rand() % (g_screenHeight - 500) + 450;
            overlap = false;
            for (const auto& mussel : g_mussel) {
                if (abs(x - mussel->getRect().x) < size &&
                    abs(y - mussel->getRect().y) < size) {
                    overlap = true;
                    break;
                }
            }
        } while (overlap);
        int pos = rand() % 2;
        Mussel* mussel = new Mussel(g_textureManager);
        mussel->init(x, y, size, size, size / 2 * (pos + 1) * 10, path[pos]);
        g_mussel.push_back(mussel);
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                g_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if(g_hook->hasReturned()) g_sound->playGrab(g_soundOn);
                    g_hook->startExtend();
                }
                if(event.key.keysym.sym == SDLK_p){
                    g_pause = !g_pause;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                g_hook->startExtend();
                break;
        }
    }
}

void Game::update() {
    if(g_gameState == PLAY && !g_pause){
        g_time->update();
        g_isRunning = g_time->isRunning();

        if(g_boxCollected == true ){
            delete g_box;
            g_box = new Box(g_textureManager);
            g_box->init(g_screenWidth,g_screenHeight);
            g_buff = g_box->state();
            g_boxCollected = false;
        }

        g_hook->update();
        g_explosion->update();
        g_box->update(g_screenWidth, g_screenHeight);
        for(auto& creature : g_creatures) creature->update(g_screenWidth, g_screenHeight);

        // Va chạm tĩnh vật
        if (g_hook->isExtending() && !g_hook->isAttachedCreature() && !g_hook->isAttachedMussel() && !g_hook->isAttachedBox()) {
            SDL_Point hookTip = g_hook->getTipPosition();
            for (size_t i = 0; i < g_mussel.size(); i++) {
                if (!g_mussel[i]->isCollected() && SDL_PointInRect(&hookTip, &g_mussel[i]->getRect())) {
                    g_hook->attachObject(i, g_mussel[i]->getRect().w, "mussel");
                    if(g_mussel[i]->getPath() == "bomb") {
                            g_mussel[i]->collect();
                            g_sound->playExplosion(g_soundOn);
                            g_explosion->isAttached();
                            g_score->addPoints(g_mussel[i]->getValue());
                            //g_explosion->init(hookTip.x, hookTip.y, g_mussel[i]->getRect().w);
                            g_explosion->init(g_mussel[i]->getRect().x, g_mussel[i]->getRect().y, g_mussel[i]->getRect().w);
                    }
                    break;
                }
            }
        }

        // Va chạm sinh vật
        if (g_hook->isExtending() && !g_hook->isAttachedCreature() && !g_hook->isAttachedMussel() && !g_hook->isAttachedBox()) {
            SDL_Point hookTip = g_hook->getTipPosition();
            for (size_t i = 0; i < g_creatures.size(); i++) {
                if (!g_creatures[i]->isCollected() && SDL_PointInRect(&hookTip, &g_creatures[i]->getRect())) {
                    g_hook->attachObject(i, g_creatures[i]->getRect().w,"creature");
                    break;
                }
            }
        }

        // Va chạm box
        if (g_hook->isExtending() && !g_hook->isAttachedCreature() && !g_hook->isAttachedMussel() && !g_hook->isAttachedBox()) {
            SDL_Point hookTip = g_hook->getTipPosition();
            if(!g_box->isCollected() && SDL_PointInRect(&hookTip, &g_box->getRect())){
                g_hook->attachObject(0,g_box->getRect().w,"box");
            }
        }

        // Kiểm tra hook chạm đáy màn hình
        if (g_hook->isExtending() && !g_hook->isAttachedMussel() && !g_hook->isAttachedCreature() &&
            (g_hook->getTipPosition().y >= g_screenHeight || g_hook->getTipPosition().x >= g_screenWidth || g_hook->getTipPosition().x <= 0)) {
            g_score->addPoints(-100);
            g_hook->startRetract();
            g_touchScreen = true;
        }

        // Âm thanh khi chạm đáy
        if(g_touchScreen && g_hook->hasReturned()) g_sound->playGrab(g_soundOn);
        if(g_hook->hasReturned()) g_touchScreen = false;

        // Cập nhật vị trí tĩnh vật đã bắt được
        if (g_hook->isAttachedMussel()) {
            int ObjectIndex = g_hook->getAttachedObjectIndex();
            SDL_Point hookTip = g_hook->getTipPosition();

            g_mussel[ObjectIndex]->setPosition(
                hookTip.x - g_mussel[ObjectIndex]->getRect().w / 2,
                hookTip.y - g_mussel[ObjectIndex]->getRect().h / 2
            );

        }

        // Cập nhật vị trí sinh vật đã bắt được
        if (g_hook->isAttachedCreature()) {
            int ObjectIndex = g_hook->getAttachedObjectIndex();
            SDL_Point hookTip = g_hook->getTipPosition();

            g_creatures[ObjectIndex]->setPosition(
                hookTip.x - g_creatures[ObjectIndex]->getRect().w / 2,
                hookTip.y - g_creatures[ObjectIndex]->getRect().h / 2
            );
        }

        // Cập nhật vị trí box đã bắt được
        if (g_hook->isAttachedBox()) {
            SDL_Point hookTip = g_hook->getTipPosition();

            g_box->setPosition(
                hookTip.x - g_box->getRect().w / 2,
                hookTip.y - g_box->getRect().h / 2
            );
        }

        // Kiểm tra khi hook về vị trí ban đầu
        if (g_hook->hasReturned() && g_hook->isAttachedMussel()) {

            int ObjectIndex = g_hook->getAttachedObjectIndex();
            if(g_mussel[ObjectIndex]->getPath() == "mussel") {
                g_score->addPoints(g_mussel[ObjectIndex]->getValue());
            }
            g_mussel[ObjectIndex]->collect();
            g_hook->detachObject("mussel");
            g_sound->playGrab(g_soundOn);
        }
        if (g_hook->hasReturned() && g_hook->isAttachedCreature()) {

            int ObjectIndex = g_hook->getAttachedObjectIndex();
            g_score->addPoints(g_creatures[ObjectIndex]->getValue());
            g_creatures[ObjectIndex]->collect();
            g_hook->detachObject("creature");
            g_sound->playGrab(g_soundOn);
        }
        if (g_hook->hasReturned() && g_hook->isAttachedBox()) {
            g_box->collect();
            g_hook->detachObject("box");
            g_sound->playGrab(g_soundOn);
            g_boxCollected = true;
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer);

    if (g_gameState == MENU) {
        renderMenu();
    }
    else if (g_gameState == PLAY) {
        g_textureManager->draw("background",0,0,g_screenWidth,g_screenHeight,g_renderer);
        g_textureManager->draw("fisher",g_screenWidth / 2 - FISHER_WIDTH / 2 - 44,FISHER_DISTANT,FISHER_WIDTH,FISHER_HEIGHT,g_renderer);

        g_explosion->render(g_renderer);
        for (auto& mussel : g_mussel) mussel->render(g_renderer);
        for (auto& creature : g_creatures) creature->render(g_renderer);

        g_box->render(g_renderer);
        g_hook->render(g_renderer);
        SDL_Point hookTip = g_hook->getTipPosition();
        g_textureManager->drawhook("hook", hookTip.x, hookTip.y, HOOK_WIDTH, HOOK_WIDTH,g_hook->isExtending(),g_pause,g_renderer);

        g_score->render(g_renderer);
        g_time->render(g_renderer);

        if(g_box->isCollected()) {
            // hiển thị note
            SDL_Color note = {0,0,0,0};
            g_textRenderer->renderText("Press P to continue!!",note,g_screenWidth / 2 - 80, 440);
            g_pause = true;
            if(g_buff == "extratime") {
                g_time->addTime(15*60);
                g_buff = "null";
            }
            if(g_buff == "minus") {
                g_score->addPoints(-200);
                g_buff = "null";
            }
            if(g_buff == "x2") {
                for (auto& mussel : g_mussel) mussel->setValue();
                for (auto& creature : g_creatures) creature->setValue();
                g_buff = "null";
            }
        }
        SDL_RenderPresent(g_renderer);
    }
}

void Game::clean() {
    for (auto& creature : g_creatures) delete creature;
    g_creatures.clear();

    for (auto& mussel : g_mussel) delete mussel;
    g_mussel.clear();

    delete g_box;
    delete g_sound;

    if (g_hook) {
        delete g_hook;
        g_hook = nullptr;
    }

    if (g_textureManager) {
        delete g_textureManager;
        g_textureManager = nullptr;
    }

    if (g_textRenderer) {
        delete g_textRenderer;
        g_textRenderer = nullptr;
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    IMG_Quit();
    SDL_Quit();
}

GameState Game::getGameState() const {
    return g_gameState;
}

bool Game::running() const {
    return g_isRunning;
}
