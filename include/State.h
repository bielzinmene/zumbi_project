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
    void Start();
    void Update(float dt);
    void Render();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go) const;

private:
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music m_music;
    bool m_quitRequested;
    bool m_started;
    bool m_assetsLoaded;
};

#endif // state_h