#include "../include/Game.h"
#define INCLUDE_SDL
#include "SDL_include.h"

int main() {

    Game& game = Game::GetInstance();
    game.Run();

    return 0;
}