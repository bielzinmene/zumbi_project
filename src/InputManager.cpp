#include "InputManager.h"

InputManager::InputManager()
    : m_mouseState{}, m_mouseUpdate{}, m_quitRequested(false),
      m_updateCounter(0), m_mouseX(0), m_mouseY(0) {}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::Update() {
    ++m_updateCounter;
    m_quitRequested = false;
    SDL_GetMouseState(&m_mouseX, &m_mouseY);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_quitRequested = true;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (!event.key.repeat) {
                m_keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
                m_keyUpdate[event.key.keysym.sym] = m_updateCounter;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            const int button = event.button.button;
            if (button > 0 && button < 6) {
                m_mouseState[button] = event.type == SDL_MOUSEBUTTONDOWN;
                m_mouseUpdate[button] = m_updateCounter;
            }
            m_mouseX = event.button.x;
            m_mouseY = event.button.y;
            break;
        }
        case SDL_MOUSEMOTION:
            m_mouseX = event.motion.x;
            m_mouseY = event.motion.y;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                for (auto& key : m_keyState) {
                    if (key.second) {
                        key.second = false;
                        m_keyUpdate[key.first] = m_updateCounter;
                    }
                }
                for (int button = 1; button < 6; ++button) {
                    if (m_mouseState[button]) {
                        m_mouseState[button] = false;
                        m_mouseUpdate[button] = m_updateCounter;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}

bool InputManager::IsKeyDown(int key) const {
    auto it = m_keyState.find(key);
    return it != m_keyState.end() && it->second;
}

bool InputManager::KeyPress(int key) const {
    auto it = m_keyUpdate.find(key);
    return IsKeyDown(key) && it != m_keyUpdate.end() && it->second == m_updateCounter;
}

bool InputManager::KeyRelease(int key) const {
    auto it = m_keyUpdate.find(key);
    return !IsKeyDown(key) && it != m_keyUpdate.end() && it->second == m_updateCounter;
}

bool InputManager::IsMouseDown(int button) const {
    return button > 0 && button < 6 && m_mouseState[button];
}

bool InputManager::MousePress(int button) const {
    return IsMouseDown(button) && m_mouseUpdate[button] == m_updateCounter;
}

bool InputManager::MouseRelease(int button) const {
    return button > 0 && button < 6 && m_updateCounter != 0 &&
        !m_mouseState[button] && m_mouseUpdate[button] == m_updateCounter;
}

int InputManager::GetMouseX() const { return m_mouseX; }
int InputManager::GetMouseY() const { return m_mouseY; }
bool InputManager::QuitRequested() const { return m_quitRequested; }
