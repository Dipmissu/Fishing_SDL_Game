// hook.cpp
#include "hook.h"
#include "constants.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

Hook::Hook(int x, int y, TextureManager* textureManager) :
    g_angle(ANGLE),
    g_angleHook(60),
    g_extending(false),
    g_length(HOOK_LENGTH),
    g_speed(HOOK_SPEED),
    g_movingLeft(false),
    g_attachedBox(false),
    g_attachedMussel(false),
    g_attachedCreature(false),
    g_attachedObjectIndex(-1),
    g_returned(true),
    g_textureManager(textureManager) {

    g_base = {x, y, 120, 120};
    g_tip = {x, y};
}

Hook::~Hook() {}

void Hook::update() {
    if (!g_extending) {
        g_returned = true;
        if (g_movingLeft) {
            g_angle += 1;
            if (g_angle >= 150) {
                g_movingLeft = false;
            }
        } else {
            g_angle -= 1;
            if (g_angle <= 30) {
                g_movingLeft = true;
            }
        }
    } else {
        g_returned = false;
        g_length += g_speed;

        if (g_length <= HOOK_LENGTH) {
            g_extending = false;
            g_length = HOOK_LENGTH;
            g_returned = true;
            g_speed = 5.0;
        }
    }
    // Tính toán vị trí mũi cần câu
    g_tip.x = g_base.x + g_base.w/2 + static_cast<int>(g_length * cos(g_angle * M_PI / 180.0));
    g_tip.y = g_base.y + g_base.h - 100 + static_cast<int>(g_length * sin(g_angle * M_PI / 180.0));
}

void Hook::updateHook() {
    if(!g_extending){
        if (g_movingLeft) {
            g_angleHook += 1;
        }
        else {
            g_angleHook -= 1;
        }
    }
}

void Hook::render(SDL_Renderer* renderer) {

    // Vẽ dây câu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu đen
    SDL_RenderDrawLine(renderer,
                      g_base.x + g_base.w/2,
                      g_base.y + g_base.h - 100,
                      g_tip.x, g_tip.y);

    SDL_Point rotationPoint = {1, 0};
    SDL_Rect destRect = {g_tip.x - 2, g_tip.y, HOOK_WIDTH, HOOK_WIDTH};
    g_textureManager->drawhook("hook", g_angleHook, destRect, rotationPoint,renderer);
}

void Hook::startExtend() {
    if (!g_extending) {
        g_extending = true;
        g_returned = false;
    }
}

void Hook::startRetract() {
    if (g_extending) {
        g_speed = -g_speed; // Đảo chiều
    }
}

void Hook::attachObject(int index, int ObjectSize, string id) {
    if(id == "mussel"){
        g_attachedMussel = true;
    }
    else if(id == "creature"){
        g_attachedCreature = true;
    }
    else {
        g_attachedBox = true;
    }
    g_attachedObjectIndex = index;

    // Điều chỉnh tốc độ kéo về dựa trên kích thước vật
    g_speed = 3.0 / (ObjectSize / 20.0);
    if (g_speed > 0) g_speed = -g_speed; // Đảm bảo tốc độ âm để kéo về
}

void Hook::detachObject(string id) {
    if(id == "mussel"){
        g_attachedMussel = false;
    }
    else if(id == "creature"){
        g_attachedCreature = false;
    }
    else {
        g_attachedBox = false;
    }
    g_attachedObjectIndex = -1;
    g_speed = 5.0; // Reset tốc độ
}
