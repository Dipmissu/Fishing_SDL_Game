// creature.cpp
#include "creature.h"
#include <cstdlib>

Creature::Creature(TextureManager* textureManager) :
    g_speed(1.5f),
    g_visible(false),
    g_textureManager(textureManager),
    g_frameCount(6),
    g_currentFrame(0),
    g_frameTime(0),
    g_frameDelay(1.0f){

    g_rect = {0, 0, 48, 48};
}

Creature::~Creature() {
    // Không hủy textureManager vì nó thuộc quản lý bên ngoài
}

void Creature::init(int frameCount) {
    g_frameCount = frameCount;
    g_frameDelay = 1.0f;
}

void Creature::update(float deltaTime, int screenWidth, int screenHeight) {
    // Cập nhật animation
    g_frameTime += deltaTime * 4;
    if (g_frameTime >= g_frameDelay) {
        g_frameTime = 0;
        g_currentFrame = (g_currentFrame + 1) % g_frameCount;
    }

    if (!g_visible && (std::rand() / (float)RAND_MAX) < 0.01f) {  // Xác suất chính xác hơn
        g_visible = true;
        g_rect.x = -10;
        g_rect.y = 50 + std::rand() % (screenHeight - 400) + 300;  // Giới hạn tránh ra khỏi màn hình
    }

    // Di chuyển nếu hiển thị
    if (g_visible) {
        g_rect.x += g_speed;
        if (g_rect.x > screenWidth + 50) {
            g_visible = false;
        }
    }
}

void Creature::render(SDL_Renderer* renderer) {
    if (g_visible) {
        g_textureManager->drawFrame("creature", g_rect.x, g_rect.y, g_rect.w, g_rect.h,
                                    0, g_currentFrame, renderer);
    }
}
