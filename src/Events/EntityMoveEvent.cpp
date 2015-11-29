#include "EntityMoveEvent.h"
#include <iostream>

EntityMoveEvent::EntityMoveEvent(unsigned int unitID, unsigned int newTileID, unsigned int lastTileID, const sf::Vector2f &oldPosition, const sf::Vector2f &newPosition)
    : MessageBase(Types::entityMoveEvent)
{
    //ctor
    this->unitID = unitID;
    this->newTileID = newTileID;
    this->lastTileID = lastTileID;
    this->oldPosition = oldPosition;
    this->newPosition = newPosition;

    if(newTileID != lastTileID)
        this->changedTile = true;
    else
        this->changedTile = false;

}

EntityMoveEvent::~EntityMoveEvent()
{
    //dtor
}

std::unique_ptr<EntityMoveEvent> EntityMoveEvent::make(unsigned int unitID, unsigned int newTileID, unsigned int lastTileID, const sf::Vector2f &oldPos, const sf::Vector2f &newPos)
{
    return std::unique_ptr<EntityMoveEvent>(new EntityMoveEvent(unitID, newTileID, lastTileID, oldPos, newPos));
}

unsigned int EntityMoveEvent::getUnitID()
{
    return unitID;
}

bool EntityMoveEvent::didChangeTile()
{
    return changedTile;
}

unsigned int EntityMoveEvent::getNewTileID()
{
    return newTileID;
}

unsigned int EntityMoveEvent::getLastTileID()
{
    return lastTileID;
}

const sf::Vector2f &EntityMoveEvent::getOldPosition()
{
    return oldPosition;
}

const sf::Vector2f &EntityMoveEvent::getNewPosition()
{
    return newPosition;
}

