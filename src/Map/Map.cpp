#include "Map.h"

#include "SpecialTileContainer.h"
#include "AnimatedTile.h"
#include "StaticTile.h"
#include "Resources/ResourceManager.h"
#include "Utils/Globals.h"

Map::Map()
	: tileSize(32)
{
	tileTexture = ResourceManager::getInstance()->loadTexture("tilesheets/tiles.png");
	drawMin = 0;
	drawMax = mapLayerCount;

	//Resize tile storage layer count to correct number of layers
	animatedTiles.resize(mapLayerCount);
	tileStorage.resize(mapLayerCount);
	staticTileMap.resize(mapLayerCount);
}

Map::Map(const std::string& filepath)
	: Map()
{
	//Load the given map after calling the default constructor
	load(filepath);
}

Map::~Map()
{
	//dtor
}

bool Map::load(const std::string& filepath)
{
	//Open the map file
	std::ifstream file;
	file.open(filepath);
	if(!file.is_open()) //Failed to open file
		return false;

    //Set the filepath to the map's file path
    this->filepath = filepath;

	//Read map name
	std::getline(file, mapName);

	//Read map size
	file >> mapSize.x >> mapSize.y;
	mapSizePixels = sf::Vector2i(mapSize.x*tileSize, mapSize.y*tileSize);

	//Read ambient music list
	unsigned int musicCount = 0;
	file >> musicCount;
	ambientMusicList.reserve(musicCount);
	for(unsigned int a = 0; a < musicCount; a++)
	{
		std::string tempAmbientMusic;
		file >> tempAmbientMusic;
		ambientMusicList.emplace_back(tempAmbientMusic);
	}

	//Now danger music list
	file >> musicCount;
	dangerMusicList.reserve(musicCount);
	for(unsigned int a = 0; a < musicCount; a++)
	{
		std::string tempDangerMusic;
		file >> tempDangerMusic;
		dangerMusicList.emplace_back(tempDangerMusic);
	}

	//Read in special tiles
	std::string tileID;
	unsigned int tileType, argumentCount;
	std::vector<std::string> tileArguments;
	while(file.good())
	{
		file >> tileID;
		if(tileID == "END")
			break;

		file >> tileType >> argumentCount;
		for(unsigned int a = 0; a < argumentCount; a++)
		{
			tileArguments.emplace_back(std::string());
			file >> tileArguments.back();
		}
		//Register the special tile
		specialTileContainer.registerSpecialTile(tileType, stoi(tileID), tileArguments);
		tileArguments.clear();
		tileType = 0;
		argumentCount = 0;
	}


	//Read in animated/static
	int tileNumber, layerNumber, tileSheetNumber, frameCount, spriteOffsetX, spriteOffsetY, frameInterval, rotation;
	while(file >> tileNumber >> layerNumber >> tileSheetNumber >> frameCount)
	{
		if(frameCount == 1) //Normal tile as only one frame
		{
			//Allocate memory for the tile and set it up
			tileStorage[layerNumber].emplace_back(new StaticTile());

			//Store pointer to new tile for setup
			TileBase *cTile = tileStorage[layerNumber].back().get();

			//Read in sprite offset
			file >> spriteOffsetX >> spriteOffsetY;

			//Set the position of the tile
			if(tileNumber == 0) //To avoid division by 0
				cTile->setPosition(0, 0);
			else
				cTile->setPosition((tileNumber%mapSize.x)*tileSize, std::floor(tileNumber / mapSize.x)*tileSize);

			//Read in rotation (0 - up, 1 - right, 2 - down, 3 - left)
			file >> rotation;
			cTile->setRotation(rotation);

			//Set the visible texture
			cTile->setTextureRect(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
		}
		else //Animated tile as more than one frame
		{
			//Allocate memory for the animated tile and set it up
			tileStorage[layerNumber].emplace_back(new AnimatedTile());

			//Get iterator to new tile, cast to animated tile
			AnimatedTile *cTile = reinterpret_cast<AnimatedTile*>(tileStorage[layerNumber].back().get());

			//Set the tile position
			if(tileNumber == 0) //To avoid division by 0
				cTile->setPosition(0, 0);
			else
				cTile->setPosition((tileNumber%mapSize.x)*tileSize, std::floor(tileNumber / mapSize.x)*tileSize);

			//Read in each frame and add the frame to the animation
			for(int a = 0; a < frameCount; a++)
			{
				file >> spriteOffsetX >> spriteOffsetY;
				cTile->addFrame(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
			}

			//Read in the frame interval and update the animated tile
			file >> frameInterval;
			cTile->setSwitchInterval(frameInterval);

			//Store tile rotation, see static tile
			file >> rotation;
			cTile->setRotation(rotation);

			//Store a pointer to the animated tile for animated tile drawing
			animatedTiles[layerNumber].emplace_back(cTile);

			//Set default visible texture
			cTile->setTextureRect(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
		}
	}
	//Update static map
	updateStaticMap();

	file.close();
	return true;
}

void Map::updateStaticMap()
{
	//Clear the VertexArrays and create them anew
	for(unsigned int i = 0; i < mapLayerCount; i++)
	{
		staticTileMap[i].clear();
		staticTileMap[i] = sf::VertexArray(sf::Quads);
		staticTileMap[i].resize(mapSize.x*mapSize.y*4);
	}

	//Iterate through each static layer
	for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
	{
	    unsigned int cQuad = 0;
		for(unsigned int tileIndex = 0; tileIndex < tileStorage[cLayer].size(); tileIndex++) //Draw each tile to the vertex array
		{
			//Set the quad of each tile
			sf::Vertex* quad = &staticTileMap[cLayer][cQuad];//Quad is (x + y + tileIndex) * 4
			tileStorage[cLayer][tileIndex]->setQuad(quad);
			cQuad+=4;
		}
	}
}


bool Map::save(const std::string& filepath)
{
	//Change to Maps folder
	std::string newfilepath = mapPath + filepath;

	//Open output file
	std::ofstream file;
	file.open(newfilepath);
	if(!file.is_open())
		return false; //Failed to open

	//Write map metadata

	//Set the filepath to the map's file path
    this->filepath = filepath;

	//Write map name
	file.write(mapName.c_str(), mapName.size());

	//Write map size
	file << "\n" << mapSize.x << " " << mapSize.y << "\n";

	//Write ambient music list
	file << ambientMusicList.size() << " ";
	for(unsigned int a = 0; a < ambientMusicList.size(); a++)
	{
		file << ambientMusicList[a] << " ";
	}

	//Now danger music list
	file << "\n" << dangerMusicList.size() << " ";
	for(unsigned int a = 0; a < dangerMusicList.size(); a++)
	{
		file << dangerMusicList[a] << " ";
	}
	file << "\n";

	//Now for the tiles
	//Save the special tiles first
	for(unsigned int a = 0; a < specialTileContainer.getSpecialTileCount(); a++)
	{
		const SpecialTileContainer::SpecialTile &cTile = specialTileContainer.getSpecialTile(a);
		file << cTile.position << " " << cTile.tileType << " " << cTile.arguments.size();
		for(const auto &argument : cTile.arguments)
		{
			file << " " << argument;
		}
		file << "\n";
	}
	file << "END\n";

	//Save each layer of static and animated tiles in order
	for(unsigned int layer = 0; layer < getLayerCount(); layer++)
	{
		for(unsigned int tile = 0; tile < getTileCount(layer); tile++)
		{
			TileBase *cTile = tileStorage[layer][tile].get();
			if(cTile->isAnimated()) //If the tile is animated, do this
			{
				//Typecast the tile to an AnimationTile to use its specialised functions
				AnimatedTile *castTile = reinterpret_cast<AnimatedTile*>(cTile);

				//tileNumber layerNumber tileSheetNumber frameCount SpriteOffsetX SpriteOffsetY SpriteOffsetX SpriteOffsetY frameSwitchInterval Rotation
				file << tile << " " << layer << " " << 0 << " " << castTile->getFrameCount();

				//Write all frames
				for(unsigned int cFrame = 0; cFrame < castTile->getFrameCount(); cFrame++)
				{
					sf::IntRect tempFrame = castTile->getFrame(cFrame);
					file << " " << tempFrame.left << " " << tempFrame.top;
				}

				//Write remaining data
				file << " " << castTile->getSwitchInterval() << " " << castTile->getRotation() << "\n";


			}
			else //Else if the tile is not animated, do this
			{
				//tileNumber layerNumber tileSheetNumber frameCount SpriteOffsetX SpriteOffsetY Rotation
				file << tile << " " << layer << " " << 0 << " " << 1 << " " << cTile->getTextureRect().left << " " << cTile->getTextureRect().top << " " << cTile->getRotation() << "\n";
			}
		}
	}

	return true;
}

void Map::draw(sf::RenderTarget& target, const sf::RenderStates &states)
{
	//Iterate through each layer of tiles and draw each layer individually
	for(unsigned int cLayer = drawMin; cLayer < drawMax; cLayer++)
	{
		target.draw(staticTileMap[cLayer], tileTexture);
	}
}

void Map::update()
{
	//Update all animated tiles on each layer ONLY if they haven't been updated in a little while
	if(animatedTileUpdateInterval.getElapsedTime().asMilliseconds() > 100)
    {
        for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
        {
            for(auto &cTile : animatedTiles[cLayer])
                cTile->update();
        }
        animatedTileUpdateInterval.restart();
    }
}

TileBase *Map::getTile(unsigned int layer, unsigned int tileID)
{
	return tileStorage[layer][tileID].get();
}

unsigned int Map::getTileSize()
{
	return tileSize;
}

const sf::Vector2i &Map::getMapSizeTiles()
{
	return mapSize;
}

const sf::Vector2i &Map::getMapSizePixels()
{
	return mapSizePixels;
}

unsigned int Map::getTileCount(unsigned int layer)
{
	return tileStorage[layer].size();
}

unsigned int Map::getLayerCount()
{
	return mapLayerCount;
}

void Map::removeTile(unsigned int layer, unsigned int tileID)
{
	//Replace the tile with a static, transparent one
	TileBase *oldTile = tileStorage[layer][tileID].get();

	//Store old info
	auto pos = oldTile->getPosition();
	auto quad = oldTile->getQuad();
	auto rect = oldTile->getTextureRect();

	//If it's an animated tile, remove it from the AnimatedTile draw queue
	if(oldTile->isAnimated())
		animatedTiles[layer].erase(std::find(animatedTiles[layer].begin(), animatedTiles[layer].end(), dynamic_cast<AnimatedTile*>(oldTile)));

	//Replace the tile
	tileStorage[layer][tileID].reset(new StaticTile());
	TileBase *newTile = tileStorage[layer][tileID].get();

	//Update the new tile
	newTile->setTextureRect(sf::IntRect(blankTilePosition.x, blankTilePosition.y, rect.width, rect.height));
	newTile->setQuad(quad);
	newTile->setPosition(pos);
}

void Map::setMapSize(const sf::Vector2i &newSize)
{
    mapSize = newSize;

    //Clear layers
	animatedTiles.clear();
	tileStorage.clear();
	staticTileMap.clear();

	//Set to correct size
	animatedTiles.resize(mapLayerCount);
	tileStorage.resize(mapLayerCount);
	staticTileMap.resize(mapLayerCount);

	//Setup blank tiles on each layer
    for(int y = 0; y < mapSize.y; y++)
    {
        for(int x = 0; x < mapSize.x; x++)
        {
            for(unsigned int layer = 0; layer < mapLayerCount; layer++)
            {
                //Allocate memory for the tile and set it up
                tileStorage[layer].emplace_back(new StaticTile());

                //Store pointer to new tile for setup
                TileBase *cTile = tileStorage[layer].back().get();

                //Set the position of the tile
                cTile->setPosition(x*tileSize, y*tileSize);

                //Set the rotation
                cTile->setRotation(0);

                //Set the visible texture
                cTile->setTextureRect(sf::IntRect(blankTilePosition.x, blankTilePosition.y, tileSize, tileSize));
            }
        }
    }
}

void Map::setAmbientMusicList(const std::vector<std::string> &songList)
{
    ambientMusicList = songList;
}

void Map::setAggressiveMusicList(const std::vector<std::string> &songList)
{
    dangerMusicList = songList;
}

void Map::setMapName(const std::string &newName)
{
    mapName = newName;
}

const std::string &Map::getMapName()
{
    return mapName;
}

const std::string &Map::getMapFilepath()
{
    return filepath;
}

void Map::setLayerDrawRange(unsigned int drawBegin, unsigned int drawEnd)
{
    //To only draw specific layers
    drawMin = drawBegin;
    drawMax = drawEnd;
}

void Map::setTileAnimated(unsigned int layer, unsigned int tileID)
{
	//Replace the tile with a template animated one
	TileBase *oldTile = tileStorage[layer][tileID].get();

	//Store old info
	auto pos = oldTile->getPosition();
	auto rotation = oldTile->getRotation();
	auto texRect = oldTile->getTextureRect();
	auto quad = oldTile->getQuad();

	//If it's an animated tile, remove it from the AnimatedTile draw queue
	if(oldTile->isAnimated())
		animatedTiles[layer].erase(std::find(animatedTiles[layer].begin(), animatedTiles[layer].end(), dynamic_cast<AnimatedTile*>(oldTile)));

	//Replace the tile
	AnimatedTile *newTile = new AnimatedTile();
	tileStorage[layer][tileID].reset(newTile);
	animatedTiles[layer].emplace_back(newTile);

	//Update the new tile
	newTile->setPosition(pos);
	newTile->setTextureRect(texRect);
	newTile->setRotation(rotation);
	newTile->setQuad(quad);
}

void Map::setTileStatic(unsigned int layer, unsigned int tileID)
{
    removeTile(layer, tileID); //Effectively just a more intuitive name for removeTile, as this is effectively what removeTile does
}

