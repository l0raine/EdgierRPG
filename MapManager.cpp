#include "MapManager.h"

#include "Map.h"
#include "MessageHandler.h"
#include "EventTypes.h"
#include "Globals.h"

std::shared_ptr<MapManager> MapManager::instance;

MapManager::MapManager()
{
    //ctor
}

MapManager::~MapManager()
{
    //dtor
}

std::shared_ptr<MapManager> MapManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<MapManager>(new MapManager());
    }
    return instance;
}

Map* MapManager::getCurrentMap()
{
    return currentlyDisplayedMap;
}

Map* MapManager::loadMap(const std::string &filepath)
{
    //Allocate memory and load the map
    std::string newfilepath = mapPath + filepath;
    loadedMaps.emplace_back(new Map());
    if(!loadedMaps.back()->load(newfilepath))
    {
        std::cout<<"Map failed to load.\n";
        loadedMaps.pop_back();
        return nullptr;
    }

    //Update pointer to current map
    currentlyDisplayedMap = loadedMaps.back().get();
    std::cout<<"<MapManager>: Loaded Map: '"<<newfilepath<<"'"<<std::endl;

    //Dispatch map change event
    MessageHandler::getInstance()->dispatch(MapChangeEvent::make());

    return loadedMaps.back().get();
}

void MapManager::setCurrentMap(Map* cMap)
{
    currentlyDisplayedMap = cMap;
}

bool MapManager::isMapLoaded(std::unique_ptr<Map> mapToCheck)
{
    for(auto iter = loadedMaps.begin(); iter != loadedMaps.end(); iter++)
    {
        if((*iter) == mapToCheck)
            return true;
    }
    return false;
}

void MapManager::switchToMap(const std::string& filepath)
{
    unloadMap(currentlyDisplayedMap);
    loadMap(filepath);
}

void MapManager::unloadMap(Map* cMap)
{
    //Find specified map in internal list
    for(unsigned int a = 0; a < loadedMaps.size(); a++)
    {
        if(loadedMaps[a].get() == cMap)
        {
            //Remove from list, nothing else to do just yet, WIP
            loadedMaps.erase(loadedMaps.begin()+a);
            return;
        }
    }
}








