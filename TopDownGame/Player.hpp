#pragma once
#include "Actor.hpp"

class Player : public Actor {
public:
    Player(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const bool* state);

private:
    Vector2 m_Velocity;
    float m_Speed;
};