#pragma once
#include "Actor.hpp"

class Player : public Actor {
public:
    Player(class Game* game);

    // We override the Actor's update to handle our movement
    void UpdateActor(float deltaTime) override;

    // We'll also need a way to process input specifically for the player
    void ProcessKeyboard(const bool* state);

private:
    Vector2 m_Velocity;
    float m_Speed;
};