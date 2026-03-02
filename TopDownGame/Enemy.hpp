#pragma once
#include "Actor.hpp"

class Enemy : public Actor {
public:
    Enemy(class Game* game);

    // We override UpdateActor to handle the bouncing logic
    void UpdateActor(float deltaTime) override;

private:
    Vector2 m_Velocity;
    float m_Speed;
};