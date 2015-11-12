#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string &newDefaultPath)
{
    defaultPath = newDefaultPath;
}

ResourceManager::~ResourceManager()
{
    //dtor
}

bool ResourceManager::loadTexture(const std::string &filepath, std::string &saveName) noexcept
{
    std::string fullPath = defaultPath + filepath;

    sf::Texture *texture;
    if(!texture->loadFromFile(filepath))
        return false;
    loadedTextures.emplace_back(std::make_pair(saveName, texture));
    return true;
}
