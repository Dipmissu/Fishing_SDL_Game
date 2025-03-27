// texturemanager.h
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

using namespace std;

class TextureManager {
private:
    std::map<std::string, SDL_Texture*> g_textureMap;

public:
    TextureManager();
    ~TextureManager();

    bool loadTexture(const string& id, const string& path, SDL_Renderer* renderer);
    void draw(const string& id, int x, int y, int width, int height,
              SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawhook(const string& id, int x, int y, int width, int height,  bool extending,
                  SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(const string& id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer* renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    void clean();
};
