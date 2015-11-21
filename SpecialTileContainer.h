#ifndef SPECIALTILECONTAINER_H
#define SPECIALTILECONTAINER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

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

            const std::string getTileVisualID() const //Returns for example 'B' for block or 'W' for warp
            {
                switch(tileType)
                {
                case 0: //Block
                    return "B";
                    break;
                case 1: //Warp
                    return "W";
                    break;
                case 3: //Lua
                    return "L";
                    break;
                default:
                    return "U";
                }
            }

            const sf::Color getTileVisualColour() const //Returns the colour that the ID should be
            {
                switch(tileType)
                {
                case 0: //Block
                    return sf::Color::Red;
                    break;
                case 1: //Warp
                    return sf::Color::Blue;
                    break;
                case 3: //Lua
                    return sf::Color::Green;
                    break;
                default:
                    return sf::Color::White;
                }
            }
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
