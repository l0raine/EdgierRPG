#include "StaticRenderable.h"

namespace sys
{
StaticRenderable::StaticRenderable()
: physicsSystem(nullptr)
{
    //ctor
}

StaticRenderable::~StaticRenderable()
{
    //dtor
}

void StaticRenderable::draw(sf::RenderTarget* target) const
{
    //Iterate through each component and render it
    for(const auto &c : components)
    {
        target->draw(c.second.vertices, c.second.renderTexture);
    }
}

void StaticRenderable::update(float dt)
{

}

void StaticRenderable::handleMessage(std::unique_ptr<MessageBase> message)
{
    if(message->getMessageType() == MessageBase::entityDrawEvent)
    {
        if(physicsSystem != nullptr)
        {
            for(auto &c : components)
            {
                EntityDrawEvent *event = dynamic_cast<EntityDrawEvent*>(message.get());

                sf::Vector2f &pos = event->getPosition();
                sf::Vector2f &size = event->getSize();

                sf::VertexArray &r = c.second.vertices;

                r[1].position = pos;
                r[2].position = sf::Vector2f(pos.x + size.x, pos.y);
                r[3].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
                r[0].position = sf::Vector2f(pos.x, pos.y + size.y);
            }
        }
    }
}

}
