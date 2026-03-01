#include "Actor.hpp"
#include "Game.hpp"
#include <algorithm>

Actor::Actor(Game* game)
    : m_State(EActive)
    , m_Position({ 0.0f, 0.0f })
    , m_Scale(1.0f)
    , m_Game(game)
{
    m_Game->AddActor(this);
}

Actor::~Actor()
{
    m_Game->RemoveActor(this);
}

void Actor::Update(float deltaTime)
{
    if (m_State == EActive)
    {
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
    // To be overridden by subclasses (like Player)
}