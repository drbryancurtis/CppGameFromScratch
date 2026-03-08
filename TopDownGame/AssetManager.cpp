#include "AssetManager.hpp"
#include "Game.hpp"
#include "Logger.hpp"

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

    // 2. If not found, load it using SDL
    // For now, we use BMP. Later we can add SDL_image for PNGs.
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
    if (!surface) {
        Logger::LogSDLError("Failed to load image: " + filename);
        return nullptr;
    }

    // 3. Convert surface to a GPU texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Game->GetRenderer(), surface);
    SDL_DestroySurface(surface); // We don't need the CPU-side surface anymore

    if (!texture) {
        Logger::LogSDLError("Failed to create texture from: " + filename);
        return nullptr;
    }

    // 4. Store it in the map and return
    m_Textures[filename] = texture;
    Logger::Log(LogLevel::INFO, "Loaded asset: " + filename);
    return texture;
}

void AssetManager::Clear() {
    for (auto& pair : m_Textures) {
        SDL_DestroyTexture(pair.second);
    }
    m_Textures.clear();
}