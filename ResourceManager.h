#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<vector>
#include<memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"


class ResourceManager
{
    public:
        static  std::shared_ptr<ResourceManager> getInstance();
        virtual ~ResourceManager();

        sf::Texture* loadTexture(const std::string filepath) noexcept; //Load a texture by passing the path relative to Textures folder.
    protected:
    private:
        static std::shared_ptr<ResourceManager> instance;//Instance

        ResourceManager();//Private constructor for Singleton design

        std::vector<std::pair<std::string, sf::Texture*>> loadedTextures;
        std::string defaultPath;
};

#endif // RESOURCEMANAGER_H
