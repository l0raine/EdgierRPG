#ifndef SPECIALTILECONTAINER_H
#define SPECIALTILECONTAINER_H

#include <vector>

#include "Map.h"

class SpecialTileContainer
{
    public:
        struct SpecialTile
        {
            unsigned int tileType; //ID of the special tile, 0 = block, etc
            std::vector<std::string> arguments;
        };
        /** Default constructor */
        SpecialTileContainer();
        /** Default destructor */
        virtual ~SpecialTileContainer();

        void registerSpecialTile();
    protected:
    private:
        std::vector<SpecialTile> specialTiles;

};

#endif // SPECIALTILECONTAINER_H
