#include "StaticTile.h"

StaticTile::StaticTile()
{
    //ctor
    quad = nullptr;
}

StaticTile::~StaticTile()
{
    //dtor
}

sf::Vertex *StaticTile::getQuad()
{
    return quad;
}

void StaticTile::setQuad(sf::Vertex *newQuad)
{
    quad = newQuad;
    updateQuadPosition();
    updateProjectedTexture();
}
