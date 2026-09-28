#ifndef GAME_H
#define GAME_H

#include "State.h"
#include <memory>
#include <string>
#include <vector>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

class Game {
public:
    ~Game();
    static Game& GetInstance();
    SDL_Renderer* GetRenderer() const;
    State& GetCurrentState() const;
    State& GetState() const;
    void Push(State* state);
    bool AdvanceFrame(float dt);
    void Run();
    float GetDeltaTime() const;

private:
    Game(const std::string& title, int width, int height);
    void CalculateDeltaTime();

    static Game* s_instance;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::vector<std::unique_ptr<State>> m_stateStack;
    std::unique_ptr<State> m_nextState;
    Uint32 m_frameStart;
    float m_dt;
};

#endif
