#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

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

        std:;string getDisplayName();
        void setMaximumHealth(std::string newName);

        unsigned int getDirection();
        void setDirection(int newDirection);

        unsigned int getMapID();
        void setMapID(unsigned int newMapID);

        unsigned int getEntityID();
        void setEntityID(unsigned int newID);

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
};

#endif // ENTITYBASE_H
