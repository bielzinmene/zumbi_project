#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();

    ~State();

    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    Sprite m_bg;
    Music m_music;
    bool m_quitRequested;
};

#endif