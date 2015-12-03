#ifndef ENTITYDRAWEVENT_H
#define ENTITYDRAWEVENT_H

#include<SFML/Graphics.hpp>

#include <Messaging/MessageBase.h>


class EntityDrawEvent : public MessageBase
{
    public:
        EntityDrawEvent(sf::Vector2f size, sf::Vector2f position);

        static std::unique_ptr<EntityDrawEvent> make(sf::Vector2f size, sf::Vector2f position);

        sf::Vector2f& getSize();
        sf::Vector2f& getPosition();

        virtual ~EntityDrawEvent();
    protected:
    private:
        sf::Vector2f size;
        sf::Vector2f position;
};

#endif // ENTITYDRAWEVENT_H
