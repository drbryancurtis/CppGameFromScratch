#include "Game.hpp"
#include "Player.hpp"
#include <algorithm>

Game::Game()
    : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(true)
    , m_TicksCount(0), m_UpdatingActors(false), m_Player(nullptr) {
}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    m_Window = SDL_CreateWindow("Spectral Engine", 1024, 768, 0);
    if (!m_Window) return false;
    m_Renderer = SDL_CreateRenderer(m_Window, NULL);
    if (!m_Renderer) return false;

    m_TicksCount = SDL_GetTicks();
    m_Player = new Player(this); // This automatically calls AddActor
    return true;
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) m_IsRunning = false;
    }
    const bool* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) m_IsRunning = false;
    m_Player->ProcessKeyboard(state);
}

void Game::Update() {
    uint64_t timeToWait = m_TicksCount + 16 - SDL_GetTicks();
    if (timeToWait > 0 && timeToWait <= 16) SDL_Delay((uint32_t)timeToWait);

    float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    m_TicksCount = SDL_GetTicks();

    m_UpdatingActors = true;
    for (auto actor : m_Actors) {
        actor->Update(deltaTime);
    }
    m_UpdatingActors = false;

    for (auto pending : m_PendingActors) {
        m_Actors.emplace_back(pending);
    }
    m_PendingActors.clear();

    // Logic for deleting Dead actors would go here
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 255);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    Vector2 pos = m_Player->GetPosition();
    SDL_FRect playerRect = { pos.x - 16, pos.y - 16, 32, 32 };
    SDL_RenderFillRect(m_Renderer, &playerRect);

    SDL_RenderPresent(m_Renderer);
}

void Game::AddActor(Actor* actor) {
    if (m_UpdatingActors) m_PendingActors.emplace_back(actor);
    else m_Actors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor) {
    auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
    if (iter != m_PendingActors.end()) m_PendingActors.erase(iter);

    iter = std::find(m_Actors.begin(), m_Actors.end(), actor);
    if (iter != m_Actors.end()) m_Actors.erase(iter);
}

void Game::RunLoop() {
    while (m_IsRunning) {
        ProcessInput();
        Update();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    // Delete all actors in the system
    while (!m_Actors.empty()) {
        delete m_Actors.back(); // The Actor destructor handles removing itself from the vector
    }

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}