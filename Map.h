#ifndef MAP_H
#define MAP_H

#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class TileBase;
class AnimatedTile;

class Map
{
	public:
		Map();
		Map(const std::string &filepath);
		virtual ~Map();

		//Core map functions
		bool load(const std::string &filepath);
		bool save(const std::string &filepath);
		void draw(sf::RenderTarget &target, const sf::RenderStates &states);

		//Minimal map interface
		void update(); //Updates animated tiles
		void updateStaticMap(); //Re-renders the static tiles
		unsigned int getTileSize(); //Returns the tile width/height
		TileBase *getTile(unsigned int layer, unsigned int tileID); //Gets the tile at the requested layer/tileID
		const sf::Vector2i &getMapSizeTiles(); //Returns map size in tiles
		const sf::Vector2i &getMapSizePixels();
		unsigned int getTileCount(unsigned int layer); //Returns the number of tiles on a layer
		unsigned int getLayerCount(); //Returns number of layers, use this externally instead of the global mapLayerCount
		void removeTile(unsigned int layer, unsigned int tileID); //Removes a tile
	
	protected:
	
	private:
		//Map data
		std::string filepath;
		std::string mapName;
		sf::Vector2i mapSize;
		std::vector<std::string> ambientMusicList;
		std::vector<std::string> dangerMusicList;
		std::vector<std::vector<std::unique_ptr<TileBase>>> tileStorage;
		std::vector<std::vector<AnimatedTile*>> animatedTiles;
		unsigned int tileSize;
		sf::Vector2i mapSizePixels;

		//Storage for pre-rendered static tile layers
		std::vector<sf::VertexArray> staticTileMap;

		//Temporary tile texture for everything
		sf::Texture* tileTexture;
};

#endif // MAP_H
