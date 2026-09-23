#include "../include/Game.h"
#define INCLUDE_SDL
#include "SDL_include.h"

int main(int argc, char** argv) {

    Game& game = Game::GetInstance();
    game.Run();
    delete &game;

    return 0;
}