#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<vector>
#include <SFML/Graphics.hpp>
#include <iostream>


class ResourceManager
{
    public:
        ResourceManager(std::string&);
        virtual ~ResourceManager();

        bool loadTexture(const std::string &filepath, std::string &saveName) noexcept;
    protected:
    private:
        std::vector<std::pair<std::string, sf::Texture*>> loadedTextures;
        std::string defaultPath;

        sf::Texture* defaultTexture;
};

#endif // RESOURCEMANAGER_H
