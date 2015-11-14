#ifndef SPECIALTILECONTAINER_H
#define SPECIALTILECONTAINER_H

#include <vector>

#include "MessageBase.h"
#include "Map.h"

class SpecialTileContainer
{
    public:
        /** Default constructor */
        SpecialTileContainer();
        /** Default destructor */
        virtual ~SpecialTileContainer();


        struct SpecialTile
        {
            //Stores a single special tile, type and arguments
            SpecialTile(unsigned int type, const std::vector<std::string> &args)
            {
                tileType = type;
                arguments = args;
            }
            unsigned int tileType; //ID of the special tile, 0 = block, etc
            std::vector<std::string> arguments;
        };

        void handleMessage(std::unique_ptr<MessageBase> message); //Handle a message

        void registerSpecialTile(unsigned int tileType, const std::vector<std::string> &args); //Registers a special tile
        void clear(); //Removes all special tiles, used when, for example, switching map
    protected:
    private:
        std::vector<SpecialTile> specialTiles;

};

#endif // SPECIALTILECONTAINER_H
