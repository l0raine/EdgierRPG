#include "EntityBase.h"

EntityBase::EntityBase()
{
    //ctor

}

EntityBase::~EntityBase()
{
    //dtor
}

void EntityBase::draw(sf::RenderTarget& target)
{
    sprite.draw(target);
}

void EntityBase::update()
{
    sprite.update();
}

void EntityBase::setPosition(sf::Vector2f pos)
{
    position = pos;
}

sf::Vector2f EntityBase::getPosition()
{
    return position;
}
