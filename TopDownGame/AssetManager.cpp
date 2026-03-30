#include "AssetManager.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include <SDL3_image/SDL_image.h>

AssetManager::AssetManager(Game* game) : m_Game(game) {}

AssetManager::~AssetManager() {
    Clear();
}

SDL_Texture* AssetManager::GetTexture(const std::string& filename) {
    // 1. Check if we already loaded this texture
    auto it = m_Textures.find(filename);
    if (it != m_Textures.end()) {
        return it->second;
    }

    // 2. Load the texture directly using SDL_image (Supports PNG, JPG, BMP)
    SDL_Texture* texture = IMG_LoadTexture(m_Game->GetRenderer(), filename.c_str());

    if (!texture) {
        // SDL3_image pipes errors directly into the main SDL error system
        Logger::Log(LogLevel::ERR, "Failed to load " + filename + ": " + std::string(SDL_GetError()));
        return nullptr;
    }

    // 3. Store it in the map and return
    m_Textures[filename] = texture;
    Logger::Log(LogLevel::INFO, "Loaded asset: " + filename);
    return texture;
}

void AssetManager::Clear() {
    // Clean up all GPU textures to prevent memory leaks
    for (auto& pair : m_Textures) {
        if (pair.second != nullptr) {
            SDL_DestroyTexture(pair.second);
        }
    }
    m_Textures.clear();
    Logger::Log(LogLevel::INFO, "Asset Manager: All textures destroyed.");
}