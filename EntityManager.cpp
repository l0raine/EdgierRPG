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
    for(unsigned int a = 0; a < entities.size(); a++)
    {
        target.draw(entities[a]->getVertexArray(), entities[a]->getTexture());
    }
}

void EntityManager::registerEntity(std::unique_ptr<EntityBase>& entity)
{
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

}
