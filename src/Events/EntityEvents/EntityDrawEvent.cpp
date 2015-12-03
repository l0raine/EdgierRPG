#include "EntityDrawEvent.h"

EntityDrawEvent::EntityDrawEvent(sf::Vector2f size, sf::Vector2f position)
{
    this->size = size;
    this->position = position;
}

EntityDrawEvent::~EntityDrawEvent()
{
    //dtor
}

std::unique_ptr<EntityDrawEvent> EntityDrawEvent::make(sf::Vector2f size, sf::Vector2f position)
{
    return std::unique_ptr<EntityDrawEvent>(new EntityDrawEvent(size, position));
}

sf::Vector2f& EntityDrawEvent::getSize()
{
    return size;
}

sf::Vector2f& EntityDrawEvent::getPosition()
{
    return position;
}
