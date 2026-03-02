#include "Enemy.hpp"
#include "Game.hpp"

Enemy::Enemy(Game* game)
    : Actor(game)
    , m_Speed(200.0f)
{
    // Start in the middle-ish moving diagonally
    SetPosition({ 200.0f, 200.0f });
    m_Velocity = { 0.707f, 0.707f }; // Moving down-right
}

void Enemy::UpdateActor(float deltaTime) {
    Vector2 pos = GetPosition();

    // Move the position
    pos.x += m_Velocity.x * m_Speed * deltaTime;
    pos.y += m_Velocity.y * m_Speed * deltaTime;

    // Bounce off Left/Right walls
    if (pos.x < 0.0f) {
        pos.x = 0.0f;
        m_Velocity.x *= -1.0f;
    }
    else if (pos.x > 1024.0f) {
        pos.x = 1024.0f;
        m_Velocity.x *= -1.0f;
    }

    // Bounce off Top/Bottom walls
    if (pos.y < 0.0f) {
        pos.y = 0.0f;
        m_Velocity.y *= -1.0f;
    }
    else if (pos.y > 768.0f) {
        pos.y = 768.0f;
        m_Velocity.y *= -1.0f;
    }

    SetPosition(pos);
}