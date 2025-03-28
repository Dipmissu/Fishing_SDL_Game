// texturemanager.cpp
#include "texturemanager.h"
#include "constants.h"

using namespace std;

double g_angle = 60;
bool g_movingLeft = false;

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

void TextureManager::drawhook(const string& id, int x, int y, int width, int height, bool extending,
                          SDL_Renderer* renderer, SDL_RendererFlip flip) {
    SDL_Point rotationPoint = {2, 0};
    SDL_Rect destRect = {x - 2, y, width, height};
    if(!extending){
        if (g_movingLeft) {
            g_angle += 1;
            if (g_angle >= 60) {
                g_movingLeft = false;
            }
        }
        else {
            g_angle -= 1;
            if (g_angle <= -60) {
                g_movingLeft = true;
            }
        }
    }

    if (g_textureMap.find(id) != g_textureMap.end()) {
        SDL_RenderCopyEx(renderer, g_textureMap[id], NULL, &destRect,g_angle, &rotationPoint, flip);
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
