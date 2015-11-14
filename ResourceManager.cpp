#include "ResourceManager.h"
#include <fstream>

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

    sf::Texture *texture = new sf::Texture();
    if(!texture->loadFromFile(fullPath))
        return nullptr;
    loadedTextures.insert(std::make_pair(fullPath, texture));
    std::cout<<"<ResourceManager>: Loaded texture '"<<fullPath<<"'\n";
    return texture;
}

 void ResourceManager::clearTextures()
 {
     loadedTextures.clear();
 }

sf::Texture* ResourceManager::getLoadedTexture(std::string &texture_in)
{
    if(isTextureLoaded(texture_in))
    {
        return loadedTextures.find(texture_in)->second;
    }
    return nullptr;
}

bool ResourceManager::isTextureLoaded(std::string &texture_in)
{
    if(!isTextureStorageEmpty() && loadedTextures.find(texture_in) == loadedTextures.end())
    {
        return false;
    }
    return true;
}

bool ResourceManager::isTextureStorageEmpty()
{
    if(!loadedTextures.empty())
        return false;
    return true;
}

sf::SoundBuffer* ResourceManager::loadSoundBuffer(const std::string filepath) noexcept
{
    std::string fullPath = soundPath + filepath;

    sf::SoundBuffer *buffer = new sf::SoundBuffer();
    if(!buffer->loadFromFile(fullPath))
        return nullptr;
    loadedSoundBuffers.insert(std::make_pair(fullPath, buffer));
    std::cout<<"<ResourceManager>: Loaded sound buffer '"<<fullPath<<"'\n";
    return buffer;
}

void ResourceManager::clearSoundBuffers()
{
    loadedSoundBuffers.clear();
}

sf::SoundBuffer* ResourceManager::getLoadedSound(std::string& sound_in)
{
    if(isSoundLoaded(sound_in))
    {
        return loadedSoundBuffers.find(sound_in)->second;
    }
    return nullptr;
}

bool ResourceManager::isSoundLoaded(std::string &sound_in)
{
    if(!isSoundStorageEmpty() && loadedSoundBuffers.find(sound_in) == loadedSoundBuffers.end())
    {
        return false;
    }
    return true;
}

bool ResourceManager::isSoundStorageEmpty()
{
    if(!loadedSoundBuffers.empty())
        return false;
    return true;
}

bool ResourceManager::writeFile(const std::string &filepath_in, std::string &data_out)
{
    std::ofstream file;
    file.open(filepath_in, std::ios::out | std::ios::binary);
    if(!file.is_open())
        return false; //Failed to open file
    file.write(data_out.c_str(), data_out.length()); // Write the data
    file.close(); //Close the stream
    return true;
}
