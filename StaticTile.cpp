#include "StaticTile.h"

StaticTile::StaticTile()
{
    //ctor
}

StaticTile::~StaticTile()
{
    //dtor
}

const sf::Vector2f &StaticTile::getPosition()
{
    return position;
}

void StaticTile::setPosition(float x, float y)
{
    //Update position
    position.x = x;
    position.y = y;

    //Update global bounds
    floatRect.left = x;
    floatRect.top = y;
    floatRect.width = 32;
    floatRect.height = 32;
}

int StaticTile::getRotation()
{
    return rotation;
}

void StaticTile::setRotation(int &newRotation)
{
    rotation = newRotation;
}

void StaticTile::setPosition(const sf::Vector2f& newPos)
{
    position = newPos;
}

const sf::FloatRect &StaticTile::getGlobalBounds()
{
    return floatRect;
}

void StaticTile::setTextureRect(const sf::IntRect &newRect)
{
    intRect = newRect;
}

const sf::IntRect &StaticTile::getTextureRect()
{
    return intRect;
}
