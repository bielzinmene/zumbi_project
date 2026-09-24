#ifndef CHARACTER_H
#define CHARACTER_H
#include "Component.h"
#include "Timer.h"
#include "Sound.h"
#include "Vec2.h"
#include <memory>
#include <queue>
#include <string>

class Character : public Component {
public:
    enum class CommandType { MOVE, SHOOT };
    struct Command {
        CommandType type;
        Vec2 pos;
        Command(CommandType type, float x, float y) : type(type), pos(x, y) {}
    };
    Character(GameObject& associated, const std::string& sprite);
    ~Character() override;
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject& other) override;
    void Issue(Command task);
    bool IsAlive() const;
    const GameObject& GetObject() const;
    static Character* player;

private:
    std::weak_ptr<GameObject> m_weapon;
    std::queue<Command> m_commands;
    Vec2 m_velocity;
    float m_moveSpeed;
    int m_health;
    bool m_facingLeft;
    Timer m_deathTimer;
    Timer m_damageCooldown;
    Sound m_hitSound;
    Sound m_deathSound;
    void TakeDamage(int amount);
};
#endif
