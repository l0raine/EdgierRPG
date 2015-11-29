#include "ResourceManager.h"

#include "Utils/Globals.h"

//Define static instance variable once
std::shared_ptr<ResourceManager> ResourceManager::instance;
std::shared_ptr<SoundHandler> ResourceManager::soundHandlerInstance;


ResourceManager::ResourceManager()
{
    defaultFont.loadFromFile(guiFontPath);
    std::cout << "\nFont address: " << &defaultFont;
}

std::shared_ptr<ResourceManager> ResourceManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<ResourceManager>(new ResourceManager);
    }
    return instance;
}

std::shared_ptr<SoundHandler> ResourceManager::getSoundHandler()
{
    if(soundHandlerInstance == nullptr)
    {
        soundHandlerInstance= std::shared_ptr<SoundHandler>(new SoundHandler);
    }
    return soundHandlerInstance;
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

sf::Texture* ResourceManager::getLoadedTexture(const std::string &texture_in)
{
    if(isTextureLoaded(texture_in))
    {
        return loadedTextures.find(texturePath + texture_in)->second;
    }
    std::string fullpath = texturePath + texture_in;
    std::cout << "\n<ResourceManager>: Get loaded texture failed for path: " + fullpath;
    return nullptr;
}

bool ResourceManager::isTextureLoaded(const std::string &texture_in)
{
    std::string fullPath = texturePath + texture_in;
    if(!isTextureStorageEmpty() || loadedTextures.find(fullPath) == loadedTextures.end())
    {
        return true;
    }
    return false;
}

bool ResourceManager::isTextureStorageEmpty()
{
    if(!loadedTextures.empty())
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

const sf::Font &ResourceManager::getDefaultFont()
{
    return defaultFont;
}
