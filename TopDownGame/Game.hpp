#pragma once
#include "Math.hpp"
#include <SDL3/SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

private:
    void ProcessInput();
    void Update();
    void GenerateOutput();

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    bool m_IsRunning;

    // Time tracking
    uint64_t m_TicksCount;

    // The Engine's "Registry"
    std::vector<class Actor*> m_Actors;          // Active actors
    std::vector<class Actor*> m_PendingActors;   // Actors waiting to be added
    bool m_UpdatingActors;                       // Safety lock for the loop
};

class Player* m_Player; // A pointer to our player actor