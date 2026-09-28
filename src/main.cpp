#include "Game.h"
#include "TitleState.h"

int main() {
    Game& game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();
    delete &game;
    return 0;
}
