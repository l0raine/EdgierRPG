#include "EntityManager.h"

#include "MessageBase.h"
#include "EntityBase.h"
#include "Events/KeyEvent.h"
#include "InputHandler.h"
#include "EventTypes.h"

std::shared_ptr<EntityManager> EntityManager::instance;

EntityManager::EntityManager()
{
    //ctor
    selectedEntityID = 0;
    entityCounter = 0;

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
    entities.back()->setEntityID(entityCounter++);
}

void EntityManager::handleMessage(std::unique_ptr<MessageBase>& message)
{
    switch(message->getMessageType())
    {
        case MessageBase::entityMoveEvent:
        {
            EntityMoveEvent *event = dynamic_cast<EntityMoveEvent*>(message.get());
            cameraView.setCenter(entities[selectedEntityID]->getPosition());
            break;
        }

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

    //Move selected unit if needed
    if(InputHandler::getInstance()->isKeyPressed(sf::Keyboard::D))
    {
        entities[selectedEntityID]->move(2);
    }
    else if(InputHandler::getInstance()->isKeyPressed(sf::Keyboard::A))
    {
        entities[selectedEntityID]->move(3);
    }
    else if(InputHandler::getInstance()->isKeyPressed(sf::Keyboard::W))
    {
        entities[selectedEntityID]->move(0);
    }
    else if(InputHandler::getInstance()->isKeyPressed(sf::Keyboard::S))
    {
        entities[selectedEntityID]->move(1);
    }
    else
    {
        entities[selectedEntityID]->move(4); //Stop moving
    }

    //Special animation test
    if(InputHandler::getInstance()->isMousePressed(sf::Mouse::Left))
    {
        entities[selectedEntityID]->sprite.startSpecialAnimation(0);
    }
}

unsigned int EntityManager::getSelectedEntityID()
{
    return selectedEntityID;
}

EntityBase *EntityManager::getEntity(unsigned int entityID)
{
    for(auto &cEntity : entities)
    {
        if(cEntity->getEntityID() == entityID)
            return cEntity.get();
    }
    return nullptr;
}
