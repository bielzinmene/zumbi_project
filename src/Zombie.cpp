#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "GameObject.h"

Zombie::Zombie(GameObject& associated) : Component(associated), m_hitpoints(100) {
    // 1. Cria a renderizacao em malha de 3 colunas e 2 linhas (3x2)[cite: 1]
    SpriteRenderer* renderer = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    associated.AddComponent(renderer);

    // 2. Cria o animador e adiciona os comportamentos de frame[cite: 1]
    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10.0f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->SetAnimation("walking"); // Inicia correndo[cite: 1]

    associated.AddComponent(animator);
}

void Zombie::Damage(int damage) {
    m_hitpoints -= damage;
    if (m_hitpoints <= 0) {
        Animator* anim = associated.GetComponent<Animator>();
        if (anim != nullptr) {
            anim->SetAnimation("dead");
        }
    }
}

void Zombie::Update(float dt) {
    (void)dt;
    Damage(1); // Perde vida a cada frame temporariamente[cite: 1]
}

void Zombie::Render() { /* Vazio[cite: 1] */ }