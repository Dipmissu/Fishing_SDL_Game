// explosion.cpp

#include "explosion.h"
#include "constants.h"

Explosion::Explosion(TextureManager* textureManager):
    xPos(0),
    yPos(0),
    g_size(0),
    g_frame(0),
    g_frameTime(0),
    g_attached(false),
    g_frameDelay(FRAME_DELAY),
    g_textureManager(textureManager){
    }
Explosion::~Explosion(){}

void Explosion::isAttached(){
    g_attached = true;
}

void Explosion::init(int x, int y, int size){
    xPos = x;
    yPos = y;
    g_size = size * 2;
    g_frame = 0;
}

void Explosion::update(){
    if(g_attached == true){
        g_frameTime += 0.2;
        if (g_frameTime >= g_frameDelay) {
            g_frameTime = 0;
            g_frame++ ;
            if(g_frame > EXPLOSION_FRAME){
                g_attached = false;
            }
        }

    }
}

void Explosion::render(SDL_Renderer* renderer){
    if(g_attached == true){
            string path = to_string(g_frame);
            g_textureManager->draw(path, xPos - g_size / 4, yPos - g_size / 4, g_size, g_size, renderer);
    }
}
