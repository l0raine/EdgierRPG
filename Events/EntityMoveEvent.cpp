#include "EntityMoveEvent.h"
#include <iostream>

EntityMoveEvent::EntityMoveEvent(const sf::Vector2f &newPos, unsigned int unitID, bool changeTile, unsigned int newTileID, unsigned int lastTileID)
: MessageBase(Types::entityMoveEvent)
{
    //ctor
    this->newPosition = newPos;
    this->unitID = unitID;
    this->changedTile = changeTile;
    this->newTileID = newTileID;
    this->lastTileID = lastTileID;

}

EntityMoveEvent::~EntityMoveEvent()
{
    //dtor
}

std::unique_ptr<EntityMoveEvent> EntityMoveEvent::make(const sf::Vector2f &newPos, unsigned int unitID, bool changeTile, unsigned int newTileID, unsigned int lastTileID)
{
    return std::unique_ptr<EntityMoveEvent>(new EntityMoveEvent(newPos, unitID, changeTile, newTileID, lastTileID));
}

const sf::Vector2f &EntityMoveEvent::getNewPosition()
{
    return newPosition;
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
