#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    defaultPath = gl::texturePath;
}

ResourceManager* ResourceManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new ResourceManager;
    }

    return instance;
}

ResourceManager::~ResourceManager()
{
    //dtor
}

sf::Texture* ResourceManager::loadTexture(const std::string filepath, std::string saveName) noexcept
{
    std::string fullPath = defaultPath + filepath;

    sf::Texture *texture;
    if(!texture->loadFromFile(filepath))
        return nullptr;
    loadedTextures.emplace_back(std::make_pair(saveName, texture));
    return texture;
}
