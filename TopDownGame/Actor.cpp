#include "Actor.hpp"
#include "Game.hpp"

Actor::Actor(Game* game)
    : m_Game(game)
    , m_State(EActive)
    , m_Position({ 0.0f, 0.0f })
    , m_Scale(1.0f)
{
    m_Game->AddActor(this);
}

Actor::~Actor() {
    m_Game->RemoveActor(this);
}

void Actor::Update(float deltaTime) {
    if (m_State == EActive) {
        UpdateActor(deltaTime);
    }
}