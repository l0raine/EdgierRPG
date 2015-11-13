#include "Map.h"

Map::Map()
    : tileSize(32)
{
    //Load default tile sheet
    tileTexture.loadFromFile("texture.png");
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

    //Read map name
    std::getline(file, mapName);

    //Read map size
    file >> mapSize.x >> mapSize.y;

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

    //Read in tiles
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
                cTile->setPosition(0,0);
            else
                cTile->setPosition((tileNumber%mapSize.x)*tileSize, std::floor(tileNumber/mapSize.x)*tileSize);

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

            //Set the tile texture
            cTile->setTexture(&tileTexture);

            //Set the tile position
            if(tileNumber == 0) //To avoid division by 0
                cTile->setPosition(0,0);
            else
                cTile->setPosition((tileNumber%mapSize.x)*tileSize, std::floor(tileNumber/mapSize.x)*tileSize);

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
        }
    }
    //Update static map
    updateStaticMap();

    file.close();
    return true;
}

bool Map::save(const std::string& filepath)
{
    return true;
}

void Map::draw(sf::RenderTarget& target, const sf::RenderStates &states)
{
    //Iterate through each layer of tiles and draw each layer individually
    for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
    {
        for(auto &cTile : animatedTiles[cLayer]) //Draw animated tiles
            cTile->draw(target, states);

        target.draw(staticTileMap[cLayer], &tileTexture);
    }
}

void Map::update()
{
    //Update all animated tiles on each layer
    for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
    {
        for(auto &cTile : animatedTiles[cLayer])
            cTile->update();
    }
}

void Map::updateStaticMap()
{
    //Clear the VertexArrays and create them anew
    for(unsigned int i=0; i< mapLayerCount; i++)
    {
        staticTileMap[i].clear();
        staticTileMap[i] = sf::VertexArray(sf::Quads);
        staticTileMap[i].resize(mapSize.x*mapSize.y*4);
    }

    //Iterate through each static layer
    for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
    {
        for(unsigned int tileIndex = 0; tileIndex < tileStorage[cLayer].size(); tileIndex++) //Draw each tile to the vertex array
        {
            //Set the quad of each tile
            sf::Vertex* quad = &staticTileMap[cLayer][((tileIndex%mapSize.x)*tileSize + std::floor(tileIndex/mapSize.x)*tileSize * mapSize.x/tileSize) * 4];//Quad is (x + y + tileIndex) * 4
            tileStorage[cLayer][tileIndex]->setQuad(quad);
        }
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

const sf::Vector2i &Map::getMapSize()
{
    return mapSize;
}

unsigned int Map::getTileCount(unsigned int layer)
{
    return tileStorage[layer].size();
}

unsigned int Map::getLayerCount()
{
    return mapLayerCount;
}
