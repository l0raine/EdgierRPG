#include "Physics.h"

namespace sys
{
Physics::Physics()
 : controllerSystem(nullptr)
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

void Physics::update(float dt)
{
    //Send the physics aspects of the entity to the message stream
    for( auto &c : components)
    {
        MessageHandler::getInstance()->dispatch(EntityDrawEvent::make(c.second.size, c.second.position));
    }

}

void Physics::handleMessage(std::unique_ptr<MessageBase> message)
{

}

}
