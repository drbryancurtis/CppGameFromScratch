#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Actor.hpp"
#include "AssetManager.hpp"

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    SDL_Renderer* GetRenderer() const { return m_Renderer; }
    AssetManager* GetAssets() { return m_AssetManager; }

private:
    void ProcessInput();
    void Update();
    void GenerateOutput();

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    bool m_IsRunning;
    uint64_t m_TicksCount;

    std::vector<class Actor*> m_Actors;
    std::vector<class Actor*> m_PendingActors;
    class Player* m_Player;
    bool m_UpdatingActors;

    AssetManager* m_AssetManager;
};