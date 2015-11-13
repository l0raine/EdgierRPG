#include "ResourceManager.h"

//Define static instance variable once
std::shared_ptr<ResourceManager> ResourceManager::instance;

ResourceManager::ResourceManager()
{

}

std::shared_ptr<ResourceManager> ResourceManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<ResourceManager>(new ResourceManager);
    }

    return instance;
}

ResourceManager::~ResourceManager()
{
    //dtor
}

sf::Texture* ResourceManager::loadTexture(const std::string filepath) noexcept
{
    std::string fullPath = texturePath + filepath;

    sf::Texture *texture;
    if(!texture->loadFromFile(fullPath))
    {
        return nullptr;
    }
    loadedTextures.emplace_back(std::make_pair(fullPath, texture));
    std::cout<<"<ResourceManager>: Loaded texture '"<<fullPath<<"'\n";
    std::cout<<"Address of texture at load time: "<<texture<<std::endl;
    return texture;
}

