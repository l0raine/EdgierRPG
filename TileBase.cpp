#include "TileBase.h"

TileBase::TileBase()
{
    //ctor
}

TileBase::~TileBase()
{
    //dtor
}

void TileBase::setPosition(const sf::Vector2f &newPosition)
{
    //Update position
    position = newPosition;

    //Update global bounds
    tileRect.left = newPosition.x;
    tileRect.top = newPosition.y;
    tileRect.width = 32;
    tileRect.height = 32;

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
        quad[1].position = {tileRect.left , tileRect.top};
        quad[2].position = {tileRect.left + tileRect.width , tileRect.top };
        quad[3].position = {tileRect.left + tileRect.width, tileRect.top  + tileRect.height};
        quad[0].position = {tileRect.left, tileRect.top  + tileRect.height};
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
const sf::FloatRect &TileBase::getGlobalBounds()
{
    return tileRect;
}

