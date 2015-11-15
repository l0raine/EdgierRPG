#ifndef ENTITYMOVEEVENT_H
#define ENTITYMOVEEVENT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../MessageBase.h"

class EntityMoveEvent : public MessageBase
{
    public:
        /** Default constructor */
        EntityMoveEvent(const sf::Vector2f &newPos, unsigned int unitID, bool didChangeTile, unsigned int newTileID, unsigned int lastTileID);
        /** Default destructor */
        virtual ~EntityMoveEvent();

        static std::unique_ptr<EntityMoveEvent> make(const sf::Vector2f &newPos, unsigned int unitID, bool didChangeTile, unsigned int newTileID, unsigned int lastTileID);
        const sf::Vector2f &getNewPosition();
        unsigned int getUnitID();
        bool didChangeTile();
        unsigned int getNewTileID();
        unsigned int getLastTileID();
    protected:
    private:
        sf::Vector2f newPosition; //New position of the unit
        unsigned int unitID; //ID of the unit in question
        bool changedTile; //True if the unit has moved across to another tile, false otherwise
        unsigned int newTileID; //ID of the tile that they've moved to
        unsigned int lastTileID; //ID of the tile that they've moved from
};

#endif // ENTITYMOVEEVENT_H
