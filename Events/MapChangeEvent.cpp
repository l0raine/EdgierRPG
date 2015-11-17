#include "MapChangeEvent.h"

MapChangeEvent::MapChangeEvent()
: MessageBase(Types::mapChangeEvent)
{
    //ctor
}

MapChangeEvent::~MapChangeEvent()
{
    //dtor
}

std::unique_ptr<MapChangeEvent> MapChangeEvent::make()
{
    return std::unique_ptr<MapChangeEvent>(new MapChangeEvent());
}
