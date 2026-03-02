#include "Player.hpp"
#include "Game.hpp"

Player::Player(Game* game)
    : Actor(game)
    , m_Velocity({ 0.0f, 0.0f })
    , m_Speed(400.0f)
{
    SetPosition({ 512.0f, 384.0f });
}

void Player::ProcessKeyboard(const bool* state) {
    m_Velocity.x = 0.0f;
    m_Velocity.y = 0.0f;
    if (state[SDL_SCANCODE_W]) m_Velocity.y -= 1.0f;
    if (state[SDL_SCANCODE_S]) m_Velocity.y += 1.0f;
    if (state[SDL_SCANCODE_A]) m_Velocity.x -= 1.0f;
    if (state[SDL_SCANCODE_D]) m_Velocity.x += 1.0f;
    m_Velocity.Normalize();
}

void Player::UpdateActor(float deltaTime) {
    Vector2 pos = GetPosition();
    pos.x += m_Velocity.x * m_Speed * deltaTime;
    pos.y += m_Velocity.y * m_Speed * deltaTime;
    SetPosition(pos);
}