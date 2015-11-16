#include "HelperClass.h"

HelperClass::HelperClass()
{
    //ctor
}

HelperClass::~HelperClass()
{
    //dtor
}


unsigned int HelperClass::getTileIDFromPosition(const sf::Vector2f& position, Map &theMap)
{
    unsigned int tileSize = theMap.getTileSize();

    unsigned int tileX = std::floor(position.x/tileSize);
    unsigned int tileY = std::floor(position.y/tileSize);

    return (tileY*theMap.getMapSizeTiles().x)+tileX;
}

sf::Vector2f HelperClass::getPositionFromTileID(unsigned int tileID, Map &theMap)
{
    const sf::Vector2i &mapSize = theMap.getMapSizeTiles();
    unsigned int tileSize = theMap.getTileSize();
    return sf::Vector2f((tileID%mapSize.x)*tileSize, std::floor(tileID/mapSize.x)*tileSize);
}
