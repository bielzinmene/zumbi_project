#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <string>
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
