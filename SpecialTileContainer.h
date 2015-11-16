#ifndef SPECIALTILECONTAINER_H
#define SPECIALTILECONTAINER_H

#include <vector>
#include <memory>

class MessageBase;

class SpecialTileContainer
{
    public:
        /** Default destructor */
        virtual ~SpecialTileContainer();
        static std::shared_ptr<SpecialTileContainer> getInstance();

        struct SpecialTile
        {
            //Stores a single special tile, type and arguments
            SpecialTile(unsigned int type, unsigned int pos, const std::vector<std::string> &args)
            {
                tileType = type;
                arguments = args;
                position = pos;
            }
            unsigned int tileType; //ID of the special tile, 0 = block, etc
            std::vector<std::string> arguments;
            unsigned int position; //Tile position ID
        };


        void handleMessage(std::unique_ptr<MessageBase> &message); //Handle a message
        void registerSpecialTile(unsigned int tileType, unsigned int tilePosID, const std::vector<std::string> &args); //Registers a special tile
        void clear(); //Removes all special tiles, used when, for example, switching map
        unsigned int getSpecialTileCount(); //Returns numbers of special tiles in the map
        const SpecialTileContainer::SpecialTile &getSpecialTile(unsigned int id); //Returns a special tile at the given id
    protected:
    private:
        /** Default constructor */
        SpecialTileContainer();

        static std::shared_ptr<SpecialTileContainer> instance;

        std::vector<SpecialTile> specialTiles;

};

#endif // SPECIALTILECONTAINER_H
