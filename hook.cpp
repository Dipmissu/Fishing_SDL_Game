// hook.cpp
#include "hook.h"
#include "constants.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

Hook::Hook(int x, int y) :
    g_angle(ANGLE),
    g_extending(false),
    g_length(HOOK_LENGTH),
    g_speed(HOOK_SPEED),
    g_movingLeft(false),
    g_attachedMussel(false),
    g_attachedCreature(false),
    g_attachedObjectIndex(-1),
    g_returned(false) {

    g_base = {x - 5, y - 10, 10, 20};
    g_tip = {x, y + 10};
}

Hook::~Hook() {}

void Hook::update(float deltaTime) {
    if (!g_extending) {
        g_returned = true;
        if (g_movingLeft) {
            g_angle += 60.0 * deltaTime;
            if (g_angle >= 180.0) {
                g_movingLeft = false;
            }
        } else {
            g_angle -= 60.0 * deltaTime;
            if (g_angle <= 0) {
                g_movingLeft = true;
            }
        }
    } else {
        g_returned = false;
        g_length += g_speed;

        if (g_length <= 10.0) {
            g_extending = false;
            g_length = 10.0;
            g_returned = true;
            g_speed = 5.0;
        }
    }
    // Tính toán vị trí mũi cần câu
    g_tip.x = g_base.x + g_base.w/2 + static_cast<int>(g_length * std::cos(g_angle * M_PI / 180.0));
    g_tip.y = g_base.y + g_base.h + static_cast<int>(g_length * std::sin(g_angle * M_PI / 180.0));
}

void Hook::render(SDL_Renderer* renderer) {
    // Vẽ đế cần câu
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Màu nâu
    SDL_RenderFillRect(renderer, &g_base);

    // Vẽ dây câu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu đen
    SDL_RenderDrawLine(renderer,
                      g_base.x + g_base.w/2,
                      g_base.y + g_base.h,
                      g_tip.x, g_tip.y);

    // Vẽ mũi cần câu
    SDL_Rect hook = {g_tip.x - 3, g_tip.y - 3, 6, 6};
    SDL_RenderFillRect(renderer, &hook);
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
    g_attachedObjectIndex = index;

    // Điều chỉnh tốc độ kéo về dựa trên kích thước vàng
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
    g_attachedObjectIndex = -1;
    g_speed = 5.0; // Reset tốc độ
}
