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
    int tileNumber, layerNumber, tileSheetNumber, frameCount, spriteOffsetX, spriteOffsetY, frameInterval, rotation;
    while(file >> tileNumber >> layerNumber >> tileSheetNumber >> frameCount)
    {
        if(frameCount == 1) //Normal tile as only one frame
        {
            //Read in sprite offset
            file >> spriteOffsetX >> spriteOffsetY;

            //Read in rotation (0 - up, 1 - right, 2 - down, 3 - left)
            file >> rotation;

            //Allocate memory for the tile and set it up
            staticTiles[layerNumber].emplace_back(StaticTile());

            //Set the position of the tile
            if(tileNumber == 0) //To avoid division by 0
                staticTiles[layerNumber].back().setPosition(0,0);
            else
                staticTiles[layerNumber].back().setPosition((tileNumber%mapSizeX)*tileSize, std::floor(tileNumber/mapSizeX)*tileSize);

            //Set the rotation of the tile
            staticTiles[layerNumber].back().setRotation(rotation);

            //Set the visible texture
            staticTiles[layerNumber].back().setTextureRect(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
        }
        else //Animated tile as more than one frame
        {
            //Allocate memory for the animated tile and set it up
            animatedTiles[layerNumber].emplace_back(AnimatedTile());

            //Set the tile texture
            animatedTiles[layerNumber].back().setTexture(&tileTexture);

            //Set the tile position
            if(tileNumber == 0) //To avoid division by 0
                animatedTiles[layerNumber].back().setPosition(0,0);
            else
                animatedTiles[layerNumber].back().setPosition((tileNumber%mapSizeX)*tileSize, std::floor(tileNumber/mapSizeX)*tileSize);

            //Read in each frame and add the frame to the animation
            for(int a = 0; a < frameCount; a++)
            {
                file >> spriteOffsetX >> spriteOffsetY;
                animatedTiles[layerNumber].back().addFrame(sf::IntRect(spriteOffsetX, spriteOffsetY, tileSize, tileSize));
            }

            //Read in the frame interval and update the animated tile
            file >> frameInterval;
            animatedTiles[layerNumber].back().setSwitchInterval(frameInterval);

            file >> rotation;
            animatedTiles[layerNumber].back().setRotation(rotation);
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

void Map::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
    //Iterate through each layer of tiles and draw each layer individually
    for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
    {
        for(const auto &cTile : animatedTiles[cLayer]) //Draw animated tiles
            cTile.draw(target, states);

        target.draw(staticTileMap[cLayer], &tileTexture);
    }
}

void Map::update()
{
    //Update all animated tiles on each layer
    for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
    {
        for(auto &cTile : animatedTiles[cLayer])
            cTile.update();
    }
}

void Map::updateStaticMap()
{
    sf::IntRect tileTex;

    for(unsigned int i=0;i<mapLayerCount;i++)
    {
        staticTileMap[i].clear();
        staticTileMap[i] = sf::VertexArray(sf::Quads);
        staticTileMap[i].resize(mapSizeX*mapSizeY*4);
    }

    //Iterate through each static layer
    for(unsigned int cLayer = 0; cLayer < mapLayerCount; cLayer++)
    {
        for(unsigned int tileIndex = 0;tileIndex < staticTiles[cLayer].size();tileIndex++)//Draw each tile to the vertex array
        {
            StaticTile &cTile = staticTiles[cLayer][tileIndex];

            sf::FloatRect tileBounds = cTile.getGlobalBounds();
            sf::Vertex* quad = &staticTileMap[cLayer][((tileIndex%mapSizeX)*tileSize + std::floor(tileIndex/mapSizeX)*tileSize * mapSizeX/tileSize) * 4];//Quad is (x + y + tileIndex) * 4

            //Set each tile's position
            quad[1].position = {tileBounds.left , tileBounds.top};
            quad[2].position = {tileBounds.left + tileBounds.width , tileBounds.top };
            quad[3].position = {tileBounds.left + tileBounds.width, tileBounds.top  + tileBounds.height};
            quad[0].position = {tileBounds.left, tileBounds.top  + tileBounds.height};

            tileTex = cTile.getTextureRect();//get the texture rect of the tile to draw

            //Project the texture rect onto a quad based on rotation
            switch(cTile.getRotation())
            {
                case 0: // Up
                    quad[1].texCoords = sf::Vector2f(tileTex.left, tileTex.top);
                    quad[2].texCoords = sf::Vector2f(tileTex.left + tileTex.width , tileTex.top );
                    quad[3].texCoords = sf::Vector2f(tileTex.left + tileTex.width, tileTex.top  + tileTex.height);
                    quad[0].texCoords = sf::Vector2f(tileTex.left, tileTex.top  + tileTex.height);
                    break;
                case 1: // Right
                    quad[1].texCoords = sf::Vector2f(tileTex.left, tileTex.top  + tileTex.height);
                    quad[2].texCoords = sf::Vector2f(tileTex.left, tileTex.top);
                    quad[3].texCoords = sf::Vector2f(tileTex.left + tileTex.width , tileTex.top );
                    quad[0].texCoords = sf::Vector2f(tileTex.left + tileTex.width, tileTex.top  + tileTex.height);
                    break;
                case 2: //Down
                    quad[1].texCoords = sf::Vector2f(tileTex.left + tileTex.width, tileTex.top  + tileTex.height);
                    quad[2].texCoords = sf::Vector2f(tileTex.left, tileTex.top  + tileTex.height);
                    quad[3].texCoords = sf::Vector2f(tileTex.left, tileTex.top);
                    quad[0].texCoords = sf::Vector2f(tileTex.left + tileTex.width , tileTex.top );
                    break;
                case 3: //Left
                    quad[1].texCoords = sf::Vector2f(tileTex.left + tileTex.width , tileTex.top );
                    quad[2].texCoords = sf::Vector2f(tileTex.left + tileTex.width, tileTex.top  + tileTex.height);
                    quad[3].texCoords = sf::Vector2f(tileTex.left, tileTex.top  + tileTex.height);
                    quad[0].texCoords = sf::Vector2f(tileTex.left, tileTex.top);
                    break;
                default:
                    std::cout<<"Invalid rotation value for tile "<<tileIndex + 1<<std::endl;
            }
        }
    }
}
