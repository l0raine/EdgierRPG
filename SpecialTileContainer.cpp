#include "SpecialTileContainer.h"

#include "MessageBase.h"
#include "EventTypes.h"
#include "MapManager.h"
#include "HelperClass.h"
#include "EntityManager.h"
#include "EntityBase.h"

std::shared_ptr<SpecialTileContainer> SpecialTileContainer::instance;
SpecialTileContainer::SpecialTileContainer()
{
    //ctor
}

SpecialTileContainer::~SpecialTileContainer()
{
    //dtor
}

std::shared_ptr<SpecialTileContainer> SpecialTileContainer::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<SpecialTileContainer>(new SpecialTileContainer());
    }
    return instance;
}

void SpecialTileContainer::registerSpecialTile(unsigned int tileType, unsigned int tileID, const std::vector<std::string>& args)
{
    //Add the special tile to the list
    if(getSpecialTileFromID(tileID) == specialTiles.end())
        specialTiles.emplace_back(SpecialTile(tileType, tileID, args));
}

void SpecialTileContainer::clear()
{
    specialTiles.clear();
}

void SpecialTileContainer::handleMessage(std::unique_ptr<MessageBase> &message)
{
    //Handle events
    switch(message->getMessageType())
    {
    case MessageBase::entityMoveEvent:
        {
            EntityMoveEvent *event = dynamic_cast<EntityMoveEvent*>(message.get());
            if(event->didChangeTile()) //If an entity moved, check to see if they walked onto a special tile
            {
                for(unsigned int a = 0; a < specialTiles.size(); a++)
                {
                    if(specialTiles[a].position == event->getNewTileID()) //A unit has indeed stepped upon a special tile
                    {
                        switch(specialTiles[a].tileType)
                        {
                        case 0: //Block
                        {
                            EntityManager *eManager = EntityManager::getInstance().get();
                            EntityBase *objEntity = eManager->getEntity(eManager->getSelectedEntityID());
                            objEntity->setPosition(event->getOldPosition());
                            break;
                        }
                        case 1: //Warp
                        {
                            EntityManager *eManager = EntityManager::getInstance().get();
                            EntityBase *objEntity = eManager->getEntity(eManager->getSelectedEntityID());
                            if(specialTiles[a].arguments.size() == 1) //Warp to tile in this map, only one argument (tileID)
                            {
                                objEntity->setPosition(HelperClass::getPositionFromTileID(stoi(specialTiles[a].arguments[0]), *MapManager::getInstance()->getCurrentMap()));
                            }
                            else //Warp to another map, 2 arguments (mapPath, tileID)
                            {
                                objEntity->setPosition(HelperClass::getPositionFromTileID(stoi(specialTiles[a].arguments[1]), *MapManager::getInstance()->getCurrentMap()));
                                MapManager::getInstance()->switchToMap(specialTiles[a].arguments[0]);
                                return;

                            }
                            break;
                        }
                        case 2: //Lua script
                        {
                            break;
                        }
                        default:
                            std::cout << "\nMap contained unknown special tile ID!: " << specialTiles[a].tileType;
                        }
                    }
                }
            }
            break;
        }
    default:
        break;
    }
}

unsigned int SpecialTileContainer::getSpecialTileCount()
{
    return specialTiles.size();
}

const SpecialTileContainer::SpecialTile &SpecialTileContainer::getSpecialTile(unsigned int id)
{
    return specialTiles[id];
}

void SpecialTileContainer::removeSpecialTile(unsigned int tilePosID)
{
    auto iter = getSpecialTileFromID(tilePosID);
    if(iter != specialTiles.end())
        specialTiles.erase(iter);
}

std::vector<SpecialTileContainer::SpecialTile>::iterator SpecialTileContainer::getSpecialTileFromID(unsigned int tileOffset)
{
    for(auto iter = specialTiles.begin(); iter != specialTiles.end(); iter++)
    {
        if(iter->position == tileOffset)
        {
            return iter;
        }
    }
    return specialTiles.end();
}
