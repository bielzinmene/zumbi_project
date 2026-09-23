#include "../include/Game.h"
#include <iostream>
#include "Resources.h"

Game* Game::s_instance = nullptr;

Game::Game(const std::string& title, int width, int height)
    : m_window(nullptr), m_renderer(nullptr), m_state(nullptr) {

    if (s_instance != nullptr) {
        std::cerr << "[Game] Erro fatal: Singleton de Game violado!" << std::endl;
        exit(EXIT_FAILURE);
    }
    s_instance = this;

    // inicializacao do SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "[Game] Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // inicializacao do image
    int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imageFlags) & imageFlags) != imageFlags) {
        std::cerr << "[Game] Erro ao inicializar SDL_image: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // inicializacao do mixer
    int mixerFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    Mix_Init(mixerFlags);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "[Game] Erro ao abrir subsistema de audio: " << Mix_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    Mix_AllocateChannels(32);

    // criacao da janela
    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (m_window == nullptr) {
        std::cerr << "[Game] Erro ao criar janela: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // criacao do renderer acelerado
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        std::cerr << "[Game] Erro ao criar renderizador: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // instanciacao do estado inicial
    m_state = new State();
}

//destruidor
Game::~Game() {
    if (m_state != nullptr) {
        delete m_state;
        m_state = nullptr;
    }

    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game& Game::GetInstance() {
    if (s_instance == nullptr) {
        new Game("Gabriel Menezes - 241020803", 1200, 850);
    }
    return *s_instance;
}

SDL_Renderer* Game::GetRenderer() const {
    return m_renderer;
}

State& Game::GetState() const {
    return *m_state;
}

void Game::Run() {
    while (!m_state->QuitRequested()) {
        m_state->Update(0.0f);

        SDL_RenderClear(m_renderer);
        m_state->Render();
        SDL_RenderPresent(m_renderer);

        SDL_Delay(33);
    }

    // libera todas as texturas e audios cacheados na saida do loop
    Resources::ClearAll();
}
