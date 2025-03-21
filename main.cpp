// main.cpp
#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init("Fishing Game", 800, 600)) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();

        // Giới hạn FPS
        SDL_Delay(16);  // Khoảng 60 FPS
    }

    return 0;
}
