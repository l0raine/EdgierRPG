#ifndef ENTITYBASE_H
#define ENTITYBASE_H

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
