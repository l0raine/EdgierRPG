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
    if(physicsSystem != nullptr)
    {
        for(auto &c : components)
        {
            //Reposition vertex array according to position of sprite
            cmp::Physics *physComponent = physicsSystem->get(c.second.ID());
            sf::VertexArray &r = c.second.vertices;

            r[1].position = physComponent->position;
            r[2].position = sf::Vector2f(physComponent->position.x + physComponent->size.x, physComponent->position.y);
            r[3].position = sf::Vector2f(physComponent->position.x + physComponent->size.x, physComponent->position.y + physComponent->size.y);
            r[0].position = sf::Vector2f(physComponent->position.x, physComponent->position.y + physComponent->size.y);
        }
    }
}
}
