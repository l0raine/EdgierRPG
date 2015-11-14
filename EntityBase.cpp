#include "EntityBase.h"

EntityBase::EntityBase()
{
    //ctor

}

EntityBase::~EntityBase()
{
    //dtor
}

sf::VertexArray &EntityBase::getVertexArray()
{
    return shape;
}

sf::Texture *EntityBase::getTexture()
{
    return spriteSheet;
}
