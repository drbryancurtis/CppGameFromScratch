#include "Game.hpp"

Game::Game() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(true) {}

Game::~Game() {}

bool Game::Initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    m_Window = SDL_CreateWindow("Top-Down Shooter", 1024, 768, 0);
    if (!m_Window) return false;

    // Create a hardware-accelerated renderer
    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if (!m_Renderer) return false;

    m_TicksCount = SDL_GetTicks(); // Get the current time in ms

    m_PlayerPos = { 512.0f, 384.0f }; // Center of 1024x768
    m_PlayerVel = { 0.0f, 0.0f };
    m_PlayerSpeed = 300.0f; // Pixels per second

    m_Player = new Player(this);

    return true;
}

void Game::RunLoop() {
    while (m_IsRunning) {
        ProcessInput();
        Update();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) m_IsRunning = false;
    }

    // Get the state of the keyboard
    const bool* state = SDL_GetKeyboardState(nullptr);

    m_PlayerVel.x = 0;
    m_PlayerVel.y = 0;

    if (state[SDL_SCANCODE_W]) m_PlayerVel.y -= 1;
    if (state[SDL_SCANCODE_S]) m_PlayerVel.y += 1;
    if (state[SDL_SCANCODE_A]) m_PlayerVel.x -= 1;
    if (state[SDL_SCANCODE_D]) m_PlayerVel.x += 1;

    m_PlayerVel.Normalize();
}

void Game::Update() {
    // 1. Professional Frame Limiting
    // We calculate how long it has been since we started this frame
    uint64_t timeToWait = m_TicksCount + 16 - SDL_GetTicks();

    // If we are ahead of schedule, we yield the CPU to the OS
    if (timeToWait > 0 && timeToWait <= 16) {
        SDL_Delay((uint32_t)timeToWait);
    }

    // 2. Delta Time Calculation (Standard)
    float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;

    // Clamp delta time (to prevent "Teleporting" if the window is moved)
    if (deltaTime > 0.05f) deltaTime = 0.05f;

    m_TicksCount = SDL_GetTicks();

    // Update player position
    m_PlayerPos.x += m_PlayerVel.x * m_PlayerSpeed * deltaTime;
    m_PlayerPos.y += m_PlayerVel.y * m_PlayerSpeed * deltaTime;

    m_UpdatingActors = true;
    for (auto actor : m_Actors) {
        actor->Update(deltaTime);
    }
    m_UpdatingActors = false;

    // Move pending actors to m_Actors
    for (auto pending : m_PendingActors) {
        m_Actors.emplace_back(pending);
    }
    m_PendingActors.clear();

    // Remove dead actors (we'll implement this later)
}

void Game::GenerateOutput() {
    // 1. Clear the screen (Deep Grey/Blue - Cherno style)
    SDL_SetRenderDrawColor(m_Renderer, 33, 33, 33, 255);
    SDL_RenderClear(m_Renderer);

    // 2. Draw game objects here...
    // Create a rectangle for the player
    SDL_FRect playerRect = {
        m_PlayerPos.x - 16, // Center the 32x32 square
        m_PlayerPos.y - 16,
        32, 32
    };

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255); // White
    SDL_RenderFillRect(m_Renderer, &playerRect);

    // 3. Present the back buffer to the screen
    SDL_RenderPresent(m_Renderer);
}

void Game::Shutdown() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Game::AddActor(Actor* actor) {
    if (m_UpdatingActors) {
        m_PendingActors.emplace_back(actor);
    }
    else {
        m_Actors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    // Search in pending
    auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
    if (iter != m_PendingActors.end()) {
        m_PendingActors.erase(iter);
    }

    // Search in active
    iter = std::find(m_Actors.begin(), m_Actors.end(), actor);
    if (iter != m_Actors.end()) {
        m_Actors.erase(iter);
    }
}