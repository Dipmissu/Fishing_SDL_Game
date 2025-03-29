// main.cpp
#include "game.h"
#include "constants.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        cerr << "Failed to initialize game!" << endl;
        return 1;
    }

    while (game.running()) {
        switch(game.getgameIndex()){
            case 1:
                game.handleMenuEvents();
                break;
            case 2:
                game.handleEvents();
                break;
        }
        game.update();
        game.render();

        // Giới hạn FPS
        SDL_Delay(16);  // Khoảng 60 FPS
    }

    return 0;
}
