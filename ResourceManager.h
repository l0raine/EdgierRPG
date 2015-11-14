#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<vector>
#include<unordered_map>
#include<memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Globals.h"


class ResourceManager
{
    public:
        static  std::shared_ptr<ResourceManager> getInstance();
        virtual ~ResourceManager();

        //Texture loading functions
        sf::Texture* loadTexture(const std::string filepath) noexcept; //Load a texture by passing the path relative to Textures folder.
        void clearTextures(); //Clear all textures from storage
        sf::Texture* getLoadedTexture(std::string &texture_in); //Assign a reference of a loaded texture to a provided sound
        bool isTextureLoaded(std::string &filepath_in); //Check if texture is loaded and stored in memory
        bool isTextureStorageEmpty();// Check if loadedTextures vector is empty

        //TOTO: Replace these functions with a reference to SoundHandler (after integration)
        //Sound loading functions
        sf::SoundBuffer* loadSoundBuffer(const std::string filepath) noexcept; //Load a sound by passing the path relative to Sounds folder.
        void clearSoundBuffers(); //Clear all sounds from storage
        sf::SoundBuffer* getLoadedSound(std::string &sound_in); //Assign a reference of a loaded sound to a provided sound
        bool isSoundLoaded(std::string &filepath_in); //Check if texture is loaded and stored in memory
        bool isSoundStorageEmpty();// Check if loadedTextures vector is empty

        //File utils
        bool writeFile(const std::string &filepath_in, std::string &data_out); //Write a file to memory
        bool readFile(const std::string &filepath_in, std::string &data_in); //Read a file from memory
        //bool readFile(const std::string &filepath_in, std::vector<std::string> &data_out);


    protected:
    private:
        static std::shared_ptr<ResourceManager> instance;//Instance

        ResourceManager();//Private constructor for Singleton design

        std::unordered_map<std::string, sf::Texture*> loadedTextures; //Stores loaded textures
        std::unordered_map<std::string, sf::SoundBuffer*> loadedSoundBuffers; //Stores loaded sounds
        std::string defaultPath;
        SoundHandler soundHandler;
};

#endif // RESOURCEMANAGER_H
