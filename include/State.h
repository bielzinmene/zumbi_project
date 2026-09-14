#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Music.h"

class State {
public:
    State();
    ~State();

    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void AddObject(GameObject* go);

private:
    std::vector<std::unique_ptr<GameObject>> objectArray;
    Music m_music;
    bool m_quitRequested;
};

#endif // STATE_H