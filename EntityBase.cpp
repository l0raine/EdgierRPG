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
