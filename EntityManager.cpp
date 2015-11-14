#include "EntityManager.h"
#include <iostream>

std::shared_ptr<EntityManager> EntityManager::instance;

EntityManager::EntityManager()
{
    //ctor
    selectedEntityID = 0;
    isUPressed = false, isDPressed = false, isLPressed = false, isRPressed = false;
}

EntityManager::~EntityManager()
{
    //dtor
}

void EntityManager::draw(sf::RenderTarget& target, const sf::RenderStates& states)
{
    //Iterate through each entity and draw it
    for(auto iter = entities.begin(); iter != entities.end(); iter++)
    {
        (*iter)->draw(target);
    }
}

void EntityManager::registerEntity(std::unique_ptr<EntityBase>& entity)
{
    //Take ownership and store
    entities.emplace_back(std::move(entity));
}

void EntityManager::handleMessage(std::unique_ptr<MessageBase>& message)
{
    switch(message->getMessageType())
    {
    default:
        break;
    }
}

std::shared_ptr<EntityManager> EntityManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<EntityManager>(new EntityManager());
    }
    return instance;
}


void EntityManager::removeEntity(std::unique_ptr<EntityBase> &entity)
{
    for(auto iter = entities.begin(); iter != entities.end(); iter++)
    {
        if(*iter == entity)
        {
            entities.erase(iter);
            return;
        }
    }
}

void EntityManager::update()
{
    //Update all of the entities
    for(auto iter = entities.begin(); iter != entities.end(); iter++)
    {
        (*iter)->update();
    }
}
