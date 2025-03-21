// texturemanager.h
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class TextureManager {
private:
    std::map<std::string, SDL_Texture*> g_textureMap;

public:
    TextureManager();
    ~TextureManager();

    bool loadTexture(const std::string& id, const std::string& path, SDL_Renderer* renderer);
    void draw(const std::string& id, int x, int y, int width, int height,
              SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(const std::string& id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer* renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    void clean();
};
