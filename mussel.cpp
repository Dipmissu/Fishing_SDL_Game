// mussel.cpp
#include "mussel.h"

Mussel::Mussel(TextureManager* textureManager) :
    g_value(0),
    g_collected(false),
    g_textureManager(textureManager) {

    g_rect = {0, 0, 0, 0};
}

Mussel::~Mussel() {}

void Mussel::init(int x, int y, int w, int h, int val, string path) {
    g_rect = {x, y, w, h};
    g_value = val;
    g_path = path;
    g_collected = false;
}

int Mussel::getValue(){
    return (g_path == "bomb") ? -g_value : g_value;
}

void Mussel::render(SDL_Renderer* renderer) {
    if (!g_collected ) {
        g_textureManager->draw(g_path, g_rect.x, g_rect.y, g_rect.w, g_rect.h, renderer);
    }
}

void Mussel::collect() {
    g_collected = true;
}

void Mussel::setPosition(int x, int y) {
    g_rect.x = x;
    g_rect.y = y;
}
