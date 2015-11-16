#include "TileBase.h"

#include "StaticTile.h"
#include "AnimatedTile.h"

TileBase::TileBase()
{
    //ctor
    isTileAnimated = false;
}

TileBase::~TileBase()
{
    //dtor
}

void TileBase::setPosition(const sf::Vector2f &newPosition)
{
    //Update position
    position = newPosition;

    //Update quad position
    updateQuadPosition();
}

void TileBase::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

int TileBase::getRotation()
{
    return rotation;
}

void TileBase::setRotation(int newRotation)
{
    rotation = newRotation;
    updateProjectedTexture();
}

void TileBase::setTexture(sf::Texture* newTexture)
{
    texture = newTexture;
}

void TileBase::updateProjectedTexture()
{
    //Get the tile's quad
    sf::Vertex *quad = getQuad();

    //Based on the tiles rotation, set the projected texture if the quad is set
    if(quad == nullptr)
        return;

    switch(getRotation())
    {
        case 0: // Up
            quad[1].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
            quad[2].texCoords = sf::Vector2f(textureRect.left + textureRect.width , textureRect.top );
            quad[3].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top  + textureRect.height);
            quad[0].texCoords = sf::Vector2f(textureRect.left, textureRect.top  + textureRect.height);
            break;
        case 1: // Right
            quad[1].texCoords = sf::Vector2f(textureRect.left, textureRect.top  + textureRect.height);
            quad[2].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
            quad[3].texCoords = sf::Vector2f(textureRect.left + textureRect.width , textureRect.top );
            quad[0].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top  + textureRect.height);
            break;
        case 2: //Down
            quad[1].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top  + textureRect.height);
            quad[2].texCoords = sf::Vector2f(textureRect.left, textureRect.top  + textureRect.height);
            quad[3].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
            quad[0].texCoords = sf::Vector2f(textureRect.left + textureRect.width , textureRect.top );
            break;
        case 3: //Left
            quad[1].texCoords = sf::Vector2f(textureRect.left + textureRect.width , textureRect.top );
            quad[2].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top  + textureRect.height);
            quad[3].texCoords = sf::Vector2f(textureRect.left, textureRect.top  + textureRect.height);
            quad[0].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
            break;
        default:
            throw std::string("Invalid rotation value for tile!");
    }
}

void TileBase::updateQuadPosition()
{
    //Get the tile's quad
    sf::Vertex *quad = getQuad();

    //Update the quads position if the quad is set
    if(quad != nullptr)
    {
        quad[1].position = {position.x , position.y};
        quad[2].position = {position.x + textureRect.width , position.y};
        quad[3].position = {position.x + textureRect.width, position.y  + textureRect.height};
        quad[0].position = {position.x, position.y  + textureRect.height};
    }
}

void TileBase::setTextureRect(const sf::IntRect &newRect)
{
    textureRect = newRect;
    updateProjectedTexture();
}

const sf::IntRect &TileBase::getTextureRect()
{
    return textureRect;
}

const sf::FloatRect TileBase::getGlobalBounds()
{
    return sf::FloatRect(position.x, position.y, textureRect.width, textureRect.height);
}

bool TileBase::isAnimated()
{
    return isTileAnimated;
}

const sf::Vector2f &TileBase::getPosition()
{
    return position;
}

sf::Texture *TileBase::getTexture()
{
    return texture;
}
