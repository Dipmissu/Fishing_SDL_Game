// game.cpp
#include "game.h"
#include "constants.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game() :
    g_window(nullptr),
    g_renderer(nullptr),
    g_isRunning(false),
    g_score(0),
    g_timeLeft(TIME),
    g_lastTime(0),
    g_screenWidth(SCREEN_WIDTH),
    g_screenHeight(SCREEN_HEIGHT),
    g_hook(nullptr),
    g_textureManager(nullptr) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game() {
    clean();
}

bool Game::init(const string& title, int width, int height) {
    g_screenWidth = width;
    g_screenHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               g_screenWidth, g_screenHeight, SDL_WINDOW_SHOWN);
    if (!g_window) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_renderer) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    // Khởi tạo SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }

    // Khởi tạo texture manager
    g_textureManager = new TextureManager();

    // Tải các texture
    if (!g_textureManager->loadTexture("creature_1", "D:/STUDY/FISHER/SDL_GAME/image/creature_1.png", g_renderer)) {
        cerr << "Failed to load mouse texture!" << endl;
    }

    if (!g_textureManager->loadTexture("creature_2", "D:/STUDY/FISHER/SDL_GAME/image/creature_2.png", g_renderer)) {
        cerr << "Failed to load mouse texture!" << endl;
    }

    if (!g_textureManager->loadTexture("creature_3", "D:/STUDY/FISHER/SDL_GAME/image/creature_3.png", g_renderer)) {
        cerr << "Failed to load mouse texture!" << endl;
    }

    if (!g_textureManager->loadTexture("starfish", "D:/STUDY/FISHER/SDL_GAME/image/starfish.png", g_renderer)) {
        cerr << "Failed to load mouse texture!" << endl;
    }

    if (!g_textureManager->loadTexture("treasure", "D:/STUDY/FISHER/SDL_GAME/image/treasure.png", g_renderer)) {
        cerr << "Failed to load mouse texture!" << endl;
    }

    if (!g_textureManager->loadTexture("mussel","D:/STUDY/FISHER/SDL_GAME/image/mussel.png", g_renderer)) {
        cerr << "Failed to load gold texture!" << endl;
    }

    if (!g_textureManager->loadTexture("background", "D:/STUDY/FISHER/SDL_GAME/image/background.png", g_renderer)) {
        cerr << "Failed to load background texture!" << endl;
    }

    // Khởi tạo hook
    g_hook = new Hook(g_screenWidth / 2,FISHER_DISTANT);

    // Khởi tạo sinh vật
    createCreatures();

    // Tạo các con trai
    createMussel();

    g_isRunning = true;
    g_lastTime = SDL_GetTicks();

    return true;
}

void Game::createCreatures(){
    for(auto& creature : g_creatures){
        delete creature;
    }
    g_creatures.clear();

    vector<string> path{"creature_1", "creature_2", "creature_3"};

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
        Creature* creature = new Creature(g_textureManager);
        creature->init(x, y, path[rand() % 3], CREATURE_RADIUS * 10);
        g_creatures.push_back(creature);
    }
}


void Game::createMussel() {
    for (auto& mussel : g_mussel) {
        delete mussel;
    }
    g_mussel.clear();

    vector<string> path{"mussel", "starfish", "treasure"};

    for (int i = 0; i < MUSSEL_NUMBER; i++) {
        int size = rand() % 20 + 35;
        int value = size * 10;
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
        Mussel* mussel = new Mussel(g_textureManager);
        mussel->init(x, y, size, size, value, path[rand() % 3]);
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
                    g_hook->startExtend();
                }
                break;
        }
    }
}

void Game::update() {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - g_lastTime) / 1000.0f;
    g_lastTime = currentTime;

    // Giảm thời gian
    g_timeLeft -= deltaTime;
    if (g_timeLeft <= 0) {
        g_timeLeft = 0;
        // Game over logic
        cout << "Game Over! Final Score: " << g_score << endl;
        g_isRunning = false;
    }

    // Cập nhật sinh vật
    for(auto& creature : g_creatures){
        creature->update(deltaTime, g_screenWidth, g_screenHeight);
    }

    // Cập nhật hook
    g_hook->update(deltaTime);

    // Kiểm tra va chạm với trai
    if (g_hook->isExtending() && !g_hook->isAttachedCreature() && !g_hook->isAttachedMussel()) {
        SDL_Point hookTip = g_hook->getTipPosition();

        for (size_t i = 0; i < g_mussel.size(); i++) {
            if (!g_mussel[i]->isCollected() &&
                SDL_PointInRect(&hookTip, &g_mussel[i]->getRect())) {
                g_hook->attachObject(i, g_mussel[i]->getRect().w, "mussel");
                break;
            }
        }

    }

    // Kiểm tra va chạm với sinh vật
    if (g_hook->isExtending() && !g_hook->isAttachedCreature() && !g_hook->isAttachedMussel()) {
        SDL_Point hookTip = g_hook->getTipPosition();

        for (size_t i = 0; i < g_creatures.size(); i++) {
            if (!g_creatures[i]->isCollected() &&
                SDL_PointInRect(&hookTip, &g_creatures[i]->getRect())) {
                g_hook->attachObject(i, g_creatures[i]->getRect().w,"creature");
                break;
            }
        }
    }

    // Kiểm tra hook chạm đáy màn hình
    if (g_hook->isExtending() && !g_hook->isAttachedMussel() && !g_hook->isAttachedCreature() &&
        (g_hook->getTipPosition().y >= g_screenHeight || g_hook->getTipPosition().x >= g_screenWidth || g_hook->getTipPosition().x <= 0)) {
        g_hook->startRetract();

    }

    // Cập nhật vị trí con trai đã bắt được
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

    // Kiểm tra khi hook về vị trí ban đầu
    if (g_hook->hasReturned() && g_hook->isAttachedMussel()) {
        int ObjectIndex = g_hook->getAttachedObjectIndex();

        // Cộng điểm và đánh dấu con trai đã thu thập
        g_score += g_mussel[ObjectIndex]->getValue();
        g_mussel[ObjectIndex]->collect();
        g_hook->detachObject("mussel");
    }
    if (g_hook->hasReturned() && g_hook->isAttachedCreature()) {
        int ObjectIndex = g_hook->getAttachedObjectIndex();

        // Cộng điểm và đánh dấu sinh vật đã thu thập
        g_score += g_creatures[ObjectIndex]->getValue();
        g_creatures[ObjectIndex]->collect();
        g_hook->detachObject("creature");
    }
}

void Game::render() {
    // Xóa màn hình
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255); // Màu nền
    SDL_RenderClear(g_renderer);

    // Vẽ nền
    g_textureManager->draw("background",0,0,g_screenWidth,g_screenHeight,g_renderer);

    // Vẽ các vật phẩm vàng
    for (auto& mussel : g_mussel) {
        mussel->render(g_renderer);
    }

    // Vẽ sinh vật
    for (auto& creature : g_creatures) {
        creature->render(g_renderer);
    }

    // Vẽ hook
    g_hook->render(g_renderer);

    // Hiển thị điểm số và thời gian
    stringstream scoreText;
    scoreText << "Score: " << g_score;

    std::stringstream timeText;
    timeText << "Time: " << static_cast<int>(g_timeLeft);

    // Hiển thị văn bản (giả lập)
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_Rect scoreRect = {10, 10, 100, 20};
    SDL_RenderDrawRect(g_renderer, &scoreRect);

    SDL_Rect timeRect = {g_screenWidth - 110, 10, 100, 20};
    SDL_RenderDrawRect(g_renderer, &timeRect);

    // Hiển thị màn hình
    SDL_RenderPresent(g_renderer);
}

void Game::clean() {
    // Giải phóng các đối tượng
    if (g_hook) {
        delete g_hook;
        g_hook = nullptr;
    }

    for (auto& creature : g_creatures) {
        delete creature;
    }
    g_creatures.clear();

    for (auto& mussel : g_mussel) {
        delete mussel;
    }
    g_mussel.clear();

    if (g_textureManager) {
        delete g_textureManager;
        g_textureManager = nullptr;
    }

    // Giải phóng SDL
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    IMG_Quit();
    SDL_Quit();
}

bool Game::running() const {
    return g_isRunning;
}
