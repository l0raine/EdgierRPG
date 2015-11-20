#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "EntityAnimation.h"

class EntityBase
{
    public:
        /** Default constructor */
        EntityBase();
        /** Default destructor */
        virtual ~EntityBase();

        void draw(sf::RenderTarget &target);
        void update();
        void move(int newDirection);

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f);

        float getMaximumHealth();
        void setMaximumHealth(float health);

        float getRemainingHealth();
        void setRemainingHealth(float health);

        float getMaximumMana();
        void setMaximumMana(float mana);

        float getRemainingMana();
        void setRemainingMana(float mana);

        const std::string &getDisplayName();
        void setDisplayName(const std::string &newName);

        unsigned int getDirection();
        void setDirection(int newDirection);

        unsigned int getMapID();
        void setMapID(unsigned int newMapID);

        unsigned int getEntityID();
        void setEntityID(unsigned int newID);

        float getBaseMovementSpeed();
        void setBaseMovementSpeed(float newSpeed);

        EntityAnimation sprite; //The visible aspect of the entity - will be private once setup functions are done
    protected:

    private:
        float healthMaximum;
        float healthRemaining;
        float manaMaximum;
        float manaRemaining;

        sf::Vector2f position;
        std::string displayName;
        unsigned int id;
        unsigned int direction;
        unsigned int mapID;
        float baseMovementSpeed;

        sf::Clock movementClock;
};

#endif // ENTITYBASE_H
