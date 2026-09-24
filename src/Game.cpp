#include "Game.h"
#include "InputManager.h"
#include "Resources.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

Game* Game::s_instance = nullptr;

Game::Game(const std::string& title, int width, int height)
    : m_window(nullptr), m_renderer(nullptr), m_frameStart(0), m_dt(0.0f) {
    if (s_instance != nullptr) {
        std::cerr << "[Game] instancia duplicada" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    s_instance = this;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "[Game] SDL_Init: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    const int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imageFlags) & imageFlags) != imageFlags) {
        std::cerr << "[Game] IMG_Init: " << IMG_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                      MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "[Game] Mix_OpenAudio: " << Mix_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Mix_AllocateChannels(32);
    if (TTF_Init() != 0) {
        std::cerr << "[Game] TTF_Init: " << TTF_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!m_window) {
        std::cerr << "[Game] SDL_CreateWindow: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cerr << "[Game] SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Game::~Game() {
    m_nextState.reset();
    m_stateStack.clear();
    Resources::ClearAll();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    s_instance = nullptr;
}

Game& Game::GetInstance() {
    if (!s_instance) new Game("Gabriel Menezes - 241020803", 1200, 900);
    return *s_instance;
}

SDL_Renderer* Game::GetRenderer() const { return m_renderer; }

State& Game::GetCurrentState() const {
    if (!m_stateStack.empty()) return *m_stateStack.back();
    if (m_nextState) return *m_nextState;
    throw std::logic_error("nenhum estado ativo");
}

State& Game::GetState() const { return GetCurrentState(); }

void Game::Push(State* state) {
    if (state) m_nextState.reset(state);
}

bool Game::AdvanceFrame(float dt) {
    if (!m_stateStack.empty() && m_stateStack.back()->QuitRequested()) return false;
    if (!m_stateStack.empty() && m_stateStack.back()->PopRequested()) {
        m_stateStack.pop_back();
        Resources::ClearImages();
        Resources::ClearFonts();
        Resources::ClearMusics();
        Resources::ClearSounds();
        if (!m_stateStack.empty()) m_stateStack.back()->Resume();
    }
    if (m_nextState) {
        if (!m_stateStack.empty()) m_stateStack.back()->Pause();
        m_stateStack.push_back(std::move(m_nextState));
        m_stateStack.back()->Start();
        m_frameStart = SDL_GetTicks();
        dt = 0.0f;
    }
    if (m_stateStack.empty()) return false;
    m_dt = dt;
    InputManager::GetInstance().Update();
    m_stateStack.back()->Update(dt);
    SDL_RenderClear(m_renderer);
    m_stateStack.back()->Render();
    SDL_RenderPresent(m_renderer);
    return true;
}

void Game::Run() {
    if (!m_nextState) return;
    m_frameStart = SDL_GetTicks();
    while (true) {
        CalculateDeltaTime();
        if (!AdvanceFrame(m_dt)) break;
        SDL_Delay(33);
    }
    m_nextState.reset();
    m_stateStack.clear();
    Resources::ClearImages();
    Resources::ClearFonts();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime() {
    const Uint32 now = SDL_GetTicks();
    m_dt = (now - m_frameStart) / 1000.0f;
    m_frameStart = now;
}

float Game::GetDeltaTime() const { return m_dt; }
