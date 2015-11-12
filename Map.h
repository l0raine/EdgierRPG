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
#include "StaticTile.h"

const unsigned int mapLayerCount = 5;

class Map
{
    public:
        Map();
        Map(const std::string &filepath);
        virtual ~Map();
        bool load(const std::string &filepath);
        bool save(const std::string &filepath);
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        void update(); //Updates animated tiles
        void updateStaticMap(); //Re-renders the static tiles
    protected:
    private:
        //Map data
        std::string filepath;
        std::string mapName;
        int mapSizeX;
        int mapSizeY;
        std::vector<std::string> ambientMusicList;
        std::vector<std::string> dangerMusicList;
        std::vector<StaticTile> staticTiles[mapLayerCount];
        std::vector<AnimatedTile> animatedTiles[mapLayerCount];
        unsigned int tileSize;

        //Storage for pre-rendered static tile layers
        //sf::RenderTexture staticTileMap[mapLayerCount];
        sf::VertexArray staticTileMap[mapLayerCount];

        //Temporary tile texture for everything
        sf::Texture tileTexture;
};

#endif // MAP_H
