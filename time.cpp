#include "time.h"
#include "constants.h"

Time::Time (TextureManager* textureManager, TextRenderer* textRenderer) :
    g_timeLeft(TIME),
    g_lastTime(0),
    g_textureManager(textureManager),
    g_textRenderer(textRenderer){}

void Time::addTime(int time){
    g_timeLeft += time;
}

void Time::update(){
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - g_lastTime) / 1000.0f;
    g_lastTime = currentTime;
    g_timeLeft -= deltaTime;

    if(g_timeLeft <= 0){
        g_timeLeft = 0;
        //g_running = false;
    }
}

void Time::render(SDL_Renderer* renderer){
    int time = g_timeLeft / 60.0f;
    int minute = time / 60; // Lấy số phút
    int second = time % 60; // Lấy số giây còn lại

    string minute_text = to_string(minute);
    string second_text = (second < 10) ? "0" + to_string(second) : to_string(second);
    string text = minute_text + " : " + second_text;

    SDL_Color color = {0, 0, 0, 0};
    g_textureManager->draw("board", SCREEN_WIDTH - 100, 15, BOARD_WIDTH, BOARD_HEIGHT, renderer);
    g_textureManager->draw("time", SCREEN_WIDTH - 48, 25, TIMER_RADIUS, TIMER_RADIUS, renderer);
    g_textRenderer->renderText(text, color, SCREEN_WIDTH - 90, 23);
}


