#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <map>

class AssetManager {
public:
    AssetManager(class Game* game);
    ~AssetManager();

    // Returns a texture. Loads it if it's not already in the map.
    SDL_Texture* GetTexture(const std::string& filename);

    // Clears all textures from memory
    void Clear();

private:
    class Game* m_Game;
    std::map<std::string, SDL_Texture*> m_Textures;
};