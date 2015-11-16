#include "EntityBase.h"

EntityBase::EntityBase()
{
    direction = 1;
    baseMovementSpeed = 2;
    position = sf::Vector2f(0,0);
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
    float movementOffset = movementClock.restart().asMilliseconds() * baseMovementSpeed;
    sf::Vector2f positionOld = position;
    switch(direction)
    {
        case 0:
            position.y-=movementOffset; //Moving up
            break;
        case 1:
            position.y+=movementOffset; //Moving down
            break;
        case 2:
            position.x+=movementOffset; //Moving right
            break;
        case 3:
            position.x-=movementOffset; //Moving left
            break;
        case 4:
            break; //Standing still
        default:
            std::cout<<"Invalid direction specified."<<std::endl;
    }

    if(sprite.isAnimationRunning() && positionOld == position)
    {
        sprite.stop();
    }
    else if(!sprite.isAnimationRunning() && positionOld != position)
    {
        sprite.start();
    }

    //Send movement event and calculate if we've moved a tile or not
    Map &tempMap = *MapManager::getInstance()->getCurrentMap();
    unsigned int tileIDCurrent = HelperClass::getTileIDFromPosition(position, tempMap);
    unsigned int tileIDOld = HelperClass::getTileIDFromPosition(positionOld, tempMap);

    MessageHandler::getInstance()->dispatch(EntityMoveEvent::make(id, tileIDCurrent, tileIDOld, positionOld, position));

    //After setting the directions, update the position
    sprite.setPosition(position);
    sprite.update();
}

void EntityBase::move(int newDirection)
{
    setDirection(newDirection);
}

void EntityBase::setPosition(sf::Vector2f pos)
{
    position = pos;
    sprite.setPosition(pos);
}

sf::Vector2f EntityBase::getPosition()
{
    return position;
}

float EntityBase::getMaximumHealth()
{
    return healthMaximum;
}
void EntityBase::setMaximumHealth(float health)
{
    healthMaximum = health;
}

float EntityBase::getRemainingHealth()
{
    return healthRemaining;
}
void EntityBase::setRemainingHealth(float health)
{
    healthRemaining = health;
}

float EntityBase::getMaximumMana()
{
    return manaMaximum;
}

void EntityBase::setMaximumMana(float mana)
{
    manaMaximum = mana;
}

float EntityBase::getRemainingMana()
{
    return manaRemaining;
}

void EntityBase::setRemainingMana(float mana)
{
    manaRemaining = mana;
}

std::string EntityBase::getDisplayName()
{
    return displayName;
}

void EntityBase::setDisplayName(std::string newName)
{
    displayName = newName;
}

unsigned int EntityBase::getDirection()
{
    return direction;
}

void EntityBase::setDirection(int newDirection)
{
    direction = newDirection;
    sprite.setDirection(newDirection);
}

unsigned int EntityBase::getMapID()
{
    return mapID;
}

void EntityBase::setMapID(unsigned int newMapID)
{
    mapID = newMapID;
}

unsigned int EntityBase::getEntityID()
{
    return id;
}

void EntityBase::setEntityID(unsigned int newID)
{
    id = newID;
}

float EntityBase::getBaseMovementSpeed()
{
    return baseMovementSpeed;
}

void EntityBase::setBaseMovementSpeed(float newSpeed)
{
    baseMovementSpeed = newSpeed;
}
