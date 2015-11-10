#ifndef MAP_H
#define MAP_H

#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "AnimatedTile.h"

class Map
{
    public:
        Map();
        Map(const std::string &filepath);
        virtual ~Map();
        bool load(const std::string &filepath);
        bool save(const std::string &filepath);
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        void update();
    protected:
    private:
        //Map data
        std::string filepath;
        std::string mapName;
        int mapSizeX;
        int mapSizeY;
        std::vector<std::string> ambientMusicList;
        std::vector<std::string> dangerMusicList;
        std::vector<sf::Sprite> staticTiles;
        std::vector<AnimatedTile> animatedTiles;
        unsigned int tileSize;

        //Temporary tile texture for everything
        sf::Texture tileTexture;
};

#endif // MAP_H
