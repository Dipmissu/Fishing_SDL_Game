// box.cpp
#include "box.h"
#include "constants.h"
#include <cstdlib>
#include <vector>

Box::Box (TextureManager* textureManager):
    g_collected(false),
    g_textureManager(textureManager){
    g_speed = rand() % 3 + 1;
    g_directionX = (rand() % 2 == 0) ? 1 : -1;
    g_directionY = (rand() % 2 == 0) ? 1 : -1;
    }

Box::~Box(){};

void Box::init(int screenWidth, int screenHeight){
    vector<string> buff = {"x2","15s"};
    int x = rand() % (screenWidth - 150) + 20;
    int y = rand() % (screenHeight - 300) + 250;
    g_path = buff[rand() % 2];
    g_rect = {x, y, BOX_RADIUS, BOX_RADIUS};
}

void Box::update(int screenWidth, int screenHeight){
    if(!g_collected){
        g_rect.x += g_speed * g_directionX;
        g_rect.y -= g_speed * g_directionY;
        if(g_rect.x < 0){
            g_directionX = 1;
            g_rect.x = 0;
        } else if(g_rect.x > screenWidth - BOX_RADIUS) {
            g_directionX = -1;
            g_rect.x = screenWidth - BOX_RADIUS;
        }

        if(g_rect.y < 200){
            g_directionY = -1;
            g_rect.y = 200;
        } else if(g_rect.y > screenHeight - BOX_RADIUS) {
            g_directionY = 1;
            g_rect.y = screenHeight - BOX_RADIUS;
        }
    }

}

void Box::render(SDL_Renderer* renderer){
    if(!g_collected){
        g_textureManager->draw("box",g_rect.x,g_rect.y,BOX_RADIUS,BOX_RADIUS,renderer);
    }
}

void Box::collect(){
    g_collected = true;
}

void Box::setPosition(int x, int y){
    g_rect.x = x;
    g_rect.y = y;
}





