// texturemanager.cpp
#include "texturemanager.h"
#include "constants.h"

using namespace std;

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
    clean();
}

bool TextureManager::loadTexture(const string& id, const string& path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (!tempSurface) {
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        return false;
    }

    g_textureMap[id] = texture;
    return true;
}

void TextureManager::draw(const string& id, int x, int y, int width, int height,
                          SDL_Renderer* renderer, SDL_RendererFlip flip) {
    SDL_Rect destRect = {x, y, width, height};

    if (g_textureMap.find(id) != g_textureMap.end()) {
        SDL_RenderCopyEx(renderer, g_textureMap[id], NULL, &destRect, 0, nullptr, flip);
    }
}

void TextureManager::drawhook(const string& id, double g_angle, SDL_Rect& destRect, SDL_Point& rotationPoint,
                          SDL_Renderer* renderer, SDL_RendererFlip flip) {
      if (g_textureMap.find(id) != g_textureMap.end()) {
        SDL_RenderCopyEx(renderer, g_textureMap[id], NULL, &destRect, g_angle, &rotationPoint, flip);
    }
}

void TextureManager::drawFrame(const string& id, int x, int y, int width, int height,
                              int currentRow, int currentFrame, SDL_Renderer* renderer,
                              SDL_RendererFlip flip) {
    SDL_Rect srcRect = {width * currentFrame, height * currentRow, width, height};
    SDL_Rect destRect = {x, y, 60, 60};

    if (g_textureMap.find(id) != g_textureMap.end()) {
        SDL_RenderCopyEx(renderer, g_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
    }
}

void TextureManager::clean() {
    for (auto& texture : g_textureMap) {
        SDL_DestroyTexture(texture.second);
    }
    g_textureMap.clear();
}
