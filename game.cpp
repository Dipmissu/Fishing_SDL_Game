// game.cpp
#include "game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

Game::Game() :
    g_window(nullptr),
    g_renderer(nullptr),
    g_isRunning(false),
    g_score(0),
    g_timeLeft(6000),
    g_lastTime(0),
    g_screenWidth(800),
    g_screenHeight(600),
    g_hook(nullptr),
    g_creature(nullptr),
    g_textureManager(nullptr) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Game::~Game() {
    clean();
}

bool Game::init(const std::string& title, int width, int height) {
    g_screenWidth = width;
    g_screenHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               g_screenWidth, g_screenHeight, SDL_WINDOW_SHOWN);
    if (!g_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Khởi tạo texture manager
    g_textureManager = new TextureManager();

    // Tải các texture
    if (!g_textureManager->loadTexture("creature", "D:/STUDY/FISHER/SDL_GAME/image/Walk1.png", g_renderer)) {
        std::cerr << "Failed to load mouse texture!" << std::endl;
        // Không trả về false vì có thể dùng hình chữ nhật thay thế
    }

    if (!g_textureManager->loadTexture("gold", "assets/gold.png", g_renderer)) {
        std::cerr << "Failed to load gold texture!" << std::endl;
        // Không trả về false vì có thể dùng hình chữ nhật thay thế
    }

    if (!g_textureManager->loadTexture("background", "D:/STUDY/FISHER/SDL_GAME/image/background.png", g_renderer)) {
        std::cerr << "Failed to load background texture!" << std::endl;
        // Không trả về false vì có thể dùng hình chữ nhật thay thế
    }

    // Khởi tạo hook
    g_hook = new Hook(g_screenWidth / 2, 60);

    // Khởi tạo chuột
    g_creature = new Creature(g_textureManager);
    g_creature->init(4); // 4 frames animation

    // Tạo các vật phẩm vàng
    createGoldItems();

    g_isRunning = true;
    g_lastTime = SDL_GetTicks();

    return true;
}

void Game::createGoldItems() {
    // Xóa các vật phẩm cũ nếu có
    for (auto& gold : g_goldItems) {
        delete gold;
    }
    g_goldItems.clear();

    // Tạo 10 vật phẩm vàng với kích thước và giá trị ngẫu nhiên
    for (int i = 0; i < 10; ++i) {
        int size = std::rand() % 30 + 20;  // Kích thước từ 20 đến 50
        int value = size * 10;  // Giá trị tỷ lệ với kích thước

        int x = std::rand() % (g_screenWidth - size);
        int y = std::rand() % (g_screenHeight - 200) + 150;

        Mussel* gold = new Mussel(g_textureManager);
        gold->init(x, y, size, size, value);
        g_goldItems.push_back(gold);
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
        std::cout << "Game Over! Final Score: " << g_score << std::endl;
        g_isRunning = false;
    }

    // Cập nhật chuột
    g_creature->update(deltaTime, g_screenWidth, g_screenHeight);

    // Cập nhật hook
    g_hook->update(deltaTime);

    // Kiểm tra va chạm với vàng
    if (g_hook->isExtending() && !g_hook->isAttached()) {
        SDL_Point hookTip = g_hook->getTipPosition();

        for (size_t i = 0; i < g_goldItems.size(); ++i) {
            if (!g_goldItems[i]->isCollected() &&
                SDL_PointInRect(&hookTip, &g_goldItems[i]->getRect())) {
                g_hook->attachGold(i, g_goldItems[i]->getRect().w);
                break;
            }
        }
    }

    // Kiểm tra hook chạm đáy màn hình
    if (g_hook->isExtending() && !g_hook->isAttached() &&
        (g_hook->getTipPosition().y >= g_screenHeight || g_hook->getTipPosition().x >= g_screenWidth || g_hook->getTipPosition().x <= 0)) {
        g_hook->startRetract();

    }

    // Cập nhật vị trí vàng đã bắt được
    if (g_hook->isAttached()) {
        int goldIndex = g_hook->getAttachedGoldIndex();
        SDL_Point hookTip = g_hook->getTipPosition();

        g_goldItems[goldIndex]->setPosition(
            hookTip.x - g_goldItems[goldIndex]->getRect().w / 2,
            hookTip.y - g_goldItems[goldIndex]->getRect().h / 2
        );
    }

    // Kiểm tra khi hook về vị trí ban đầu
    if (g_hook->hasReturned() && g_hook->isAttached()) {
        int goldIndex = g_hook->getAttachedGoldIndex();

        // Cộng điểm và đánh dấu vàng đã thu thập
        g_score += g_goldItems[goldIndex]->getValue();
        g_goldItems[goldIndex]->collect();
        g_hook->detachGold();
    }
}

void Game::render() {
    // Xóa màn hình
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255); // Màu nền
    SDL_RenderClear(g_renderer);

    // Vẽ nền
    g_textureManager->draw("background",0,0,g_screenWidth,g_screenHeight,g_renderer);

    // Vẽ các vật phẩm vàng
    for (auto& gold : g_goldItems) {
        gold->render(g_renderer);
    }

    // Vẽ chuột
    g_creature->render(g_renderer);

    // Vẽ hook
    g_hook->render(g_renderer);

    // Hiển thị điểm số và thời gian
    std::stringstream scoreText;
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

    if (g_creature) {
        delete g_creature;
        g_creature = nullptr;
    }

    for (auto& gold : g_goldItems) {
        delete gold;
    }
    g_goldItems.clear();

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
