#ifndef HELPERCLASS_H
#define HELPERCLASS_H

#include "Map/MapManager.h"
#include <SFML/Graphics.hpp>

class Map;
class HelperClass
{
    public:
        /** Default constructor */
        HelperClass();
        /** Default destructor */
        virtual ~HelperClass();

        static unsigned int getTileIDFromPosition(const sf::Vector2f &position, Map &theMap);
        static unsigned int getTileIDFromPosition(const sf::Vector2f &position, sf::Vector2f mapSize);
        static unsigned int getTileIDFromPosition(const sf::Vector2f& position);
        static sf::Vector2f getPositionFromTileID(unsigned int tileID, Map &theMap);

    protected:
    private:
};

#endif // HELPERCLASS_H
