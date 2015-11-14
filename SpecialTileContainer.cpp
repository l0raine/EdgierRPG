#include "SpecialTileContainer.h"

SpecialTileContainer::SpecialTileContainer()
{
    //ctor
}

SpecialTileContainer::~SpecialTileContainer()
{
    //dtor
}

void SpecialTileContainer::registerSpecialTile(unsigned int tileType, const std::vector<std::string>& args)
{
    //Add the special tile to the list
    specialTiles.emplace_back(SpecialTile(tileType, args));
}

void SpecialTileContainer::clear()
{
    specialTiles.clear();
}

void SpecialTileContainer::handleMessage(std::unique_ptr<MessageBase> message)
{
    switch(message->getMessageType())
    {

    }
}
