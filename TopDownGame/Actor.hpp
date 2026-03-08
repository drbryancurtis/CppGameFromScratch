#pragma once
#include <SDL3/SDL.h>
#include "Math.hpp"
#include <vector>

class Actor {
public:
    enum State { EActive, EPaused, EDead };

    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    virtual void UpdateActor(float deltaTime) {}

    const Vector2& GetPosition() const { return m_Position; }
    void SetPosition(const Vector2& pos) { m_Position = pos; }
    State GetState() const { return m_State; }
    void SetState(State state) { m_State = state; }

    SDL_Texture* GetTexture() const { return m_Texture; }

protected:
    class Game* m_Game;
    State m_State;
    Vector2 m_Position;
    float m_Scale;

    class SDL_Texture* m_Texture; // Pointer to the texture from the AssetManager
};