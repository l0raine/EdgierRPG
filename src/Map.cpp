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
    file >> mapSizeX >> mapSizeY;

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
    int tileNumber, layerNumber, tileSheetNumber, frameCount, spriteOffsetX, spriteOffsetY, frameInterval;
    while(file >> tileNumber >> layerNumber >> tileSheetNumber >> frameCount)
    {
        if(frameCount == 1) //Normal tile as only one frame
        {
            //Read in sprite offset
            file >> spriteOffsetX >> spriteOffsetY;

            //Allocate memory for the tile and set it up
            staticTiles.emplace_back(sf::Sprite());
            staticTiles.back().setTexture(tileTexture);

            //Set the position of the tile
            if(tileNumber == 0) //To avoid division by 0
                staticTiles.back().setPosition(0,0);
            else
                staticTiles.back().setPosition((tileNumber%mapSizeX)*32, std::floor(tileNumber/mapSizeX)*tileSize);

            //Set the visible texture
            staticTiles.back().setTextureRect(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
        }
        else //Animated tile as more than one frame
        {
            //Allocate memory for the animated tile and set it up
            animatedTiles.emplace_back(AnimatedTile());

            //Set the tile texture
            animatedTiles.back().setTexture(&tileTexture);

            //Set the tile position
            if(tileNumber == 0) //To avoid division by 0
                staticTiles.back().setPosition(0,0);
            else
                staticTiles.back().setPosition((tileNumber%mapSizeX)*tileSize, std::floor(tileNumber/mapSizeX)*tileSize);

            //Read in each frame and add the frame to the animation
            for(int a = 0; a < frameCount; a++)
            {
                file >> spriteOffsetX >> spriteOffsetY;
                animatedTiles.back().addFrame(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
            }

            //Read in the frame interval and update the animated tile
            file >> frameInterval;
            animatedTiles.back().setSwitchInterval(frameInterval);
            animatedTiles.back().update();
        }
    }
    file.close();
    return true;
}

bool Map::save(const std::string& filepath)
{
    return true;
}

void Map::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
    //Draw all animated tiles
    for(const auto &cTile : animatedTiles)
        cTile.draw(target, states);
    //Draw all static tiles
    for(const auto &cTile : staticTiles)
        target.draw(cTile, states);
}

void Map::update()
{
    //Update all animated tiles
    for(auto &cTile : animatedTiles)
        cTile.update();
}
