#pragma once
#include "Math.hpp"
#include <vector>

class Actor {
public:
    enum State { EActive, EPaused, EDead };

    Actor(class Game* game);
    virtual ~Actor();

    // Called every frame from Game
    void Update(float deltaTime);
    // Any Actor-specific update logic (to be overridden by Player)
    virtual void UpdateActor(float deltaTime);

    // Getters/Setters
    const Vector2& GetPosition() const { return m_Position; }
    void SetPosition(const Vector2& pos) { m_Position = pos; }
    float GetScale() const { return m_Scale; }
    void SetScale(float scale) { m_Scale = scale; }
    State GetState() const { return m_State; }

private:
    State m_State;
    Vector2 m_Position;
    float m_Scale;
    class Game* m_Game; // Reference to the engine "Owner"
};