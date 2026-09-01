#include "../include/State.h"
#include "../include/SDL_include.h"

State::State() : m_quitRequested(false) {
    LoadAssets();
    m_music.Play(-1);
}

State::~State() {
    m_music.Stop(0);
}

void State::LoadAssets() {
    m_bg.Open("resources/img/Background.png");
    m_music.Open("resources/audio/BGM.wav");
}

void State::Update(float dt) {
    (void)dt;

    // processa todos os eventos pendentes da janela para o SO nao travar
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // se o usuario clicou no "X"
        if (event.type == SDL_QUIT) {
            m_quitRequested = true;
        }
    }
}

void State::Render() {
    m_bg.Render(0, 0);
}

bool State::QuitRequested() const {
    return m_quitRequested;
}