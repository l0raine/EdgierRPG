#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include<vector>
#include<unordered_map>
#include<memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <SFML/Audio.hpp>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "SoundHandler.h"
class SoundHandler;

class ResourceManager
{
    public:
        static  std::shared_ptr<ResourceManager> getInstance();
        static std::shared_ptr<SoundHandler> getSoundHandler();
        virtual ~ResourceManager();

        //Texture loading functions
        sf::Texture* loadTexture(const std::string filepath) noexcept; //Load a texture by passing the path relative to Textures folder.
        void clearTextures(); //Clear all textures from storage
        sf::Texture* getLoadedTexture(const std::string &texture_in); //Assign a reference of a loaded texture to a provided sound
        bool isTextureLoaded(const std::string &filepath_in); //Check if texture is loaded and stored in memory
        bool isTextureStorageEmpty();// Check if loadedTextures vector is empty

        //File utils
        bool writeFile(const std::string &filepath_in, std::string &data_out); //Write a file to memory
        bool readFile(const std::string &filepath_in, std::string &data_in); //Read a file from memory
        //bool readFile(const std::string &filepath_in, std::vector<std::string> &data_out);


    protected:
    private:
        static std::shared_ptr<ResourceManager> instance;//Instance
        static std::shared_ptr<SoundHandler> soundHandlerInstance; //Sound handler instance


        ResourceManager();//Private constructor for Singleton design

        std::unordered_map<std::string, sf::Texture*> loadedTextures; //Stores loaded textures
        std::string defaultPath;


};

#endif // RESOURCEMANAGER_H
