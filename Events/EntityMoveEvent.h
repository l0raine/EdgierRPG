#ifndef ENTITYMOVEEVENT_H
#define ENTITYMOVEEVENT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../MessageBase.h"

class EntityMoveEvent : public MessageBase
{
    public:
        /** Default constructor */
        EntityMoveEvent(unsigned int unitID, unsigned int newTileID, unsigned int lastTileID, const sf::Vector2f &oldPosition, const sf::Vector2f &newPosition);
        /** Default destructor */
        virtual ~EntityMoveEvent();

        static std::unique_ptr<EntityMoveEvent> make(unsigned int unitID, unsigned int newTileID, unsigned int lastTileID, const sf::Vector2f &oldPosition, const sf::Vector2f &newPosition);
        unsigned int getUnitID();
        bool didChangeTile();
        unsigned int getNewTileID();
        unsigned int getLastTileID();
        const sf::Vector2f &getOldPosition();
        const sf::Vector2f &getNewPosition();
    protected:
    private:
        unsigned int unitID; //ID of the unit in question
        bool changedTile; //True if the unit has moved across to another tile, false otherwise
        unsigned int newTileID; //ID of the tile that they've moved to
        unsigned int lastTileID; //ID of the tile that they've moved from
        sf::Vector2f oldPosition; //Old position of the entity
        sf::Vector2f newPosition; //New (current) position of the entity
};

#endif // ENTITYMOVEEVENT_H
