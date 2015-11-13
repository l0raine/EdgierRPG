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
        static  ResourceManager* getInstance();
        virtual ~ResourceManager();

        sf::Texture* loadTexture(const std::string filepath, std::string saveName) noexcept;
    protected:
    private:
        static ResourceManager* instance;//Instance

        ResourceManager();//Private constructor for Singleton design

        std::vector<std::pair<std::string, sf::Texture*>> loadedTextures;
        std::string defaultPath;

        sf::Texture* defaultTexture;
};

#endif // RESOURCEMANAGER_H
