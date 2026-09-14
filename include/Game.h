#ifndef GAME_H
#define GAME_H

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"
class Game {
public:
    ~Game(); //destroyer

    //metodos
    static Game& GetInstance();
    SDL_Renderer* GetRenderer() const;
    State& GetState() const;

    void Run(); //inicialiador

private:
    Game(const std::string& title, int width, int height);//constructor
    //atributos
    static Game* s_instance;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    State* m_state;
    
};

#endif
