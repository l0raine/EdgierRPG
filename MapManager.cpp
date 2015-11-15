#include "MapManager.h"
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
    std::string newfilepath = mapPath + filepath;
    loadedMaps.emplace_back(new Map());
    if(!loadedMaps.back()->load(newfilepath))
    {
        std::cout<<"Map failed to load.\n";
        loadedMaps.pop_back();
        return nullptr;
    }
    currentlyDisplayedMap = loadedMaps.back().get();
    std::cout<<"<MapManager> Loaded Map: '"<<newfilepath<<"'"<<std::endl;
    return loadedMaps.back().get();
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
