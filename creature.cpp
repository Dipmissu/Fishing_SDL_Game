// creature.cpp
#include "creature.h"
#include "constants.h"
#include <cstdlib>

using namespace std;

Creature::Creature(TextureManager* textureManager) :
    g_value(0),
    g_collected(false),
    g_facingRight(true),
    g_textureManager(textureManager),
    g_frameCount(FRAME_COUNT),
    g_currentFrame(0),
    g_frameTime(0),
    g_frameDelay(FRAME_DELAY){
        g_speed = rand() % 2 + 1;
}

Creature::~Creature() {
}

void Creature::init(int x,int y, string path, int value) {
    g_rect = {x, y, CREATURE_RADIUS, CREATURE_RADIUS};
    g_path = path;
    g_value = value;
    g_collected = false;
}
void Creature::collect() {
    g_collected = true;
}

void Creature::update(float deltaTime, int screenWidth, int screenHeight) {
    // Cập nhật animation
    if(!g_collected){
        g_frameTime += deltaTime * 5;
        if (g_frameTime >= g_frameDelay) {
            g_frameTime = 0;
            g_currentFrame = (g_currentFrame + 1) % g_frameCount;
        }

        g_rect.x += (g_facingRight ? g_speed : -g_speed);

        if (g_rect.x <= 0 || g_rect.x >= screenWidth - CREATURE_RADIUS) {
            g_facingRight = !g_facingRight;
        }
    }
}
void Creature::render(SDL_Renderer* renderer) {
    if (!g_collected) {
        if(g_facingRight){
            g_textureManager->drawFrame(g_path, g_rect.x, g_rect.y, g_rect.w, g_rect.h, 0, g_currentFrame, renderer);
        }
        else{
            g_textureManager->drawFrame(g_path, g_rect.x, g_rect.y, g_rect.w, g_rect.h, 0, g_currentFrame, renderer,SDL_FLIP_HORIZONTAL);
        }
    }
}

void Creature::setPosition(int x, int y) {
    g_rect.x = x;
    g_rect.y = y;
}
